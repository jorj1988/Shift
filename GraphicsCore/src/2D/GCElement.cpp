#include "2D/GCElement.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "shift/Properties/scontainer.inl"
#include "MCSimpleAdd.h"
#include "XRenderer.h"
#include "Utilities/XOptional.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCInteractionHandlerPointer, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCInteractionHandler, GraphicsCore)

void GCInteractionHandler::createTypeInformation(Shift::PropertyInformationTyped<GCInteractionHandler> *,
                                      const Shift::PropertyInformationCreateData &)
  {
  }

void computeCentreOutput(GCElementCentre *e)
  {
  Shift::FloatProperty::ComputeLock l(&e->output);

  *l.data() = e->inputA() + (0.5f * e->inputB());
  }

S_IMPLEMENT_PROPERTY(GCElementCentre, GraphicsCore)

void GCElementCentre::createTypeInformation(Shift::PropertyInformationTyped<GCElementCentre> *info,
                                      const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto outInst = childBlock.overrideChild(&GCElementCentre::output);
  outInst->setCompute<computeCentreOutput>();
  }

void computeUnCentreOutput(GCElementUnCentre *e)
  {
  Shift::FloatProperty::ComputeLock l(&e->output);

  *l.data() = e->inputA() - (0.5f * e->inputB());
  }

S_IMPLEMENT_PROPERTY(GCElementUnCentre, GraphicsCore)

void GCElementUnCentre::createTypeInformation(Shift::PropertyInformationTyped<GCElementUnCentre> *info,
                                      const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto outInst = childBlock.overrideChild(&GCElementUnCentre::output);
  outInst->setCompute<computeUnCentreOutput>();
  }

void computeElementTransform(GCElement *e)
  {
  Eks::Transform t = Eks::Transform::Identity();

  t.translate(Eks::Vector3D(e->left(), e->bottom(), 0.0f));

  e->transform = t;
  }

S_IMPLEMENT_PROPERTY(GCElement, GraphicsCore)

void GCElement::createTypeInformation(Shift::PropertyInformationTyped<GCElement> *info,
                                      const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto tr = childBlock.overrideChild(&GCElement::transform);
  tr->setCompute<computeElementTransform>();

  auto affects = childBlock.createAffects(&tr, 1);

  auto vis = childBlock.add(&GCElement::visible, "visible");
  vis->setDefaultValue(true);

  auto w = childBlock.add(&GCElement::width, "width");
  w->setAffects(affects, true);
  auto h = childBlock.add(&GCElement::height, "height");
  h->setAffects(affects, false);

  auto l = childBlock.add(&GCElement::left, "left");
  l->setAffects(affects, false);
  auto b = childBlock.add(&GCElement::bottom, "bottom");
  b->setAffects(affects, false);

  childBlock.add(&GCElement::interactionHandler, "interactionHandler");
  }

const Shift::FloatProperty* GCElement::right()
  {
  MCSimpleAdd* adder = children.findChild<MCSimpleAdd>("right");
  if(!adder)
    {
    adder = addChild<MCSimpleAdd>("right");
    xAssert(adder->name() == "right");

    adder->inputA.setInput(&left);
    adder->inputB.setInput(&width);
    }
  return &adder->output;
  }

const Shift::FloatProperty* GCElement::horizontalCentre()
  {
  GCElementCentre* centre = children.findChild<GCElementCentre>("hCentre");
  if(!centre)
    {
    centre = addChild<GCElementCentre>("hCentre");
    xAssert(centre->name() == "hCentre");

    centre->inputA.setInput(&left);
    centre->inputB.setInput(&width);
    }
  return &centre->output;
  }

const Shift::FloatProperty* GCElement::verticalCentre()
  {
  GCElementCentre* centre = children.findChild<GCElementCentre>("vCentre");
  if(!centre)
    {
    centre = addChild<GCElementCentre>("vCentre");
    xAssert(centre->name() == "vCentre");

    centre->inputA.setInput(&bottom);
    centre->inputB.setInput(&height);
    }
  return &centre->output;
  }

void GCElement::setTopInput(const Shift::FloatProperty* input)
{
  xAssert(!bottom.hasInput());

  MCSimpleSubtract* top = addChild<MCSimpleSubtract>();
  top->inputA.setInput(input);

  top->inputB.setInput(&height);

  bottom.setInput(&top->output);
  }

void GCElement::setHorizontalCentreInput(const Shift::FloatProperty* input)
  {
  xAssert(!left.hasInput());

  GCElementUnCentre* centre = addChild<GCElementUnCentre>();
  centre->inputA.setInput(input);

  centre->inputB.setInput(&width);

  left.setInput(&centre->output);
  }

void GCElement::setVerticalCentreInput(const Shift::FloatProperty* input)
  {
  xAssert(!bottom.hasInput());

  GCElementUnCentre* centre = addChild<GCElementUnCentre>();
  centre->inputA.setInput(input);

  centre->inputB.setInput(&height);

  bottom.setInput(&centre->output);
  }

void GCElement::render(Eks::Renderer *r, const RenderState &state) const
  {
  if(!visible())
    {
    return;
    }

  RCTransform::render(r, state);
  }

bool GCElement::hitTest(int x, int y) const
  {
  float l = left();
  float b = bottom();

  return x >= l &&
         y >= b &&
         x < l + width() &&
         y < b + height();
  }

void computeUnitElementTransform(GCUnitElement *e)
  {
  Eks::Transform t = Eks::Transform::Identity();

  t.translate(Eks::Vector3D(e->left(), e->bottom(), 0.0f));

  t.scale(Eks::Vector3D(e->width(), e->height(), 1.0f));

  e->transform = t;
  }

S_IMPLEMENT_PROPERTY(GCElementArray, GraphicsCore)

void GCElementArray::createTypeInformation(Shift::PropertyInformationTyped<GCElementArray> *info,
                                      const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  childBlock.add(&GCElementArray::elements, "elements");
  }

GCElement *GCElementArray::addAsChild(GCElementArray *parent, RCShadingGroup *, GCElementArray **arrOpt)
  {
  Eks::Optional<GCElementArray*> arr(arrOpt);

  arr = parent->addChild<GCElementArray>();

  parent->elements.addPointer(arr);

  return arr;
  }

void GCElementArray::render(Eks::Renderer *renderer, const RenderState &state) const
  {
  GCElement::render(renderer, state);

  xForeach(auto r, elements.walker<RCRenderablePointer>())
    {
    const RCRenderable* ptd = r->pointed();
    if(!ptd)
      {
      continue;
      }

    ptd->render(renderer, state);
    }
  }

S_IMPLEMENT_PROPERTY(GCUnitElement, GraphicsCore)

void GCUnitElement::createTypeInformation(Shift::PropertyInformationTyped<GCUnitElement> *info,
                                      const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto tr = childBlock.overrideChild(&GCElement::transform);
  tr->setCompute<computeUnitElementTransform>();
  }
