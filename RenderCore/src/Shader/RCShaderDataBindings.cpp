#include "Shader/RCShaderDataBindings.h"
#include "shift/Properties/sattribute.inl"
#include "RCTexture.h"

namespace RCShaderDataBindings
{

void Vector3::bindData(DataBlock *data, const Shift::Attribute *p) const
  {
  const Shift::Vector3DProperty *c = p->uncheckedCastTo<Shift::Vector3DProperty>();

  data->resizeAndCopy(data->size() + sizeof(Eks::Vector3D), (xuint8*)c->value().data());
  }

void Vector3::getDescription(Eks::ShaderConstantDataDescription &desc, const Shift::Attribute *p) const
  {
  desc.type = Eks::ShaderConstantDataDescription::Float3;
  desc.name = p->name().data();
  }

void Vector4::bindData(DataBlock *data, const Shift::Attribute *p) const
  {
  const Shift::ColourProperty *c = p->uncheckedCastTo<Shift::ColourProperty>();

  data->resizeAndCopy(data->size() + sizeof(Eks::Colour), (xuint8*)c->value().data());
  }

void Vector4::getDescription(Eks::ShaderConstantDataDescription &desc, const Shift::Attribute *p) const
  {
  desc.type = Eks::ShaderConstantDataDescription::Float4;
  desc.name = p->name().data();
  }

void Texture2DRef::bindResource(DataBlock *, ResourceBlock *resources, const Shift::Attribute *p) const
  {
  const RCTexture2DPointer *c = p->uncheckedCastTo<RCTexture2DPointer>();

  if(c->input())
    {
    const Eks::Texture2D* newValue = &(c->pointed()->value());

    resources->pushBack(newValue);
    }
  }

void DataRef::bindResource(DataBlock *data, ResourceBlock *, const Shift::Attribute *p) const
  {
  const RCShaderConstantDataPointer *c = p->uncheckedCastTo<RCShaderConstantDataPointer>();

  if(c->input())
    {
    const Eks::ShaderConstantData* newValue = &(c->pointed()->runtimeData());

    data->pushBack(newValue);
    }
  }

}
