#include "GCShader.h"
#include "spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "sprocessmanager.h"
#include "shandlerimpl.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderComponentPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(GCShaderComponentPointerArray, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCShaderComponent, GraphicsCore)

void GCShaderComponent::createTypeInformation(SPropertyInformationTyped<GCShaderComponent> *,
                                              const SPropertyInformationCreateData &)
  {
  }

GCShaderComponent::GCShaderComponent()
  {
  }

S_IMPLEMENT_PROPERTY(GCFragmentShaderComponent, GraphicsCore)

void GCFragmentShaderComponent::createTypeInformation(SPropertyInformationTyped<GCFragmentShaderComponent> *,
                                                      const SPropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCVertexShaderComponent, GraphicsCore)

void GCVertexShaderComponent::createTypeInformation(SPropertyInformationTyped<GCVertexShaderComponent> *,
                                                    const SPropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCShader, GraphicsCore)

void GCShader::computeShaderRuntime(GCShader *shader)
  {
  xAssert(SProcessManager::isMainThread());

  GCRuntimeShader::ComputeLock lock(&shader->runtimeShader);

  if(shader->_rebuildShader)
    {
    lock.data()->clear();

    xForeach(auto cmpPtr, shader->components.walker<GCShaderComponentPointer>())
      {
      const GCShaderComponent* cmp = cmpPtr->pointed();
      if(cmp)
        {
        XAbstractShader::ComponentType t;
        if(cmp->castTo<GCFragmentShaderComponent>())
          {
          t = XAbstractShader::Fragment;
          }
        else if(cmp->castTo<GCVertexShaderComponent>())
          {
          t = XAbstractShader::Vertex;
          }
        else
          {
          xAssertFail();
          }
        lock.data()->addComponent(t, cmp->value());
        }
      }

    shader->_setVariables = true;
    }

  if(shader->_setVariables)
    {
    xForeach(auto p, shader->walkerFrom((SProperty*)&shader->components))
      {
      const GCShaderBindableData *binder = p->interface<GCShaderBindableData>();
      if(binder)
        {
        binder->bindData(lock.data(), p);
        }
      }
    }

  shader->_rebuildShader = false;
  shader->_setVariables = false;
  }

void GCShader::createTypeInformation(SPropertyInformationTyped<GCShader> *info,
                                     const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rtInfo = info->add(&GCShader::runtimeShader, "runtimeShader");
    rtInfo->setCompute<computeShaderRuntime>();
    rtInfo->setComputeLockedToMainThread(true);

    auto comInfo = info->add(&GCShader::components, "components");
    comInfo->setAffects(rtInfo);
    }
  }

GCShader::GCShader()
  {
  _setVariables = true;
  _rebuildShader = true;
  }

void GCShader::bind(XRenderer *r) const
  {
  r->setShader(&runtimeShader());
  }

void GCShader::postChildSet(SPropertyContainer *c, SProperty *p)
  {
  ParentType::postChildSet(c, p);

  GCShader *shader = c->uncheckedCastTo<GCShader>();

  if(p == &shader->runtimeShader)
    {
    return;
    }

  if(shader->components.isDirty())
    {
    shader->_rebuildShader = true;
    }
  else
    {
    shader->_setVariables = true;
    }
  }
