#include "mcsimpleadd.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"

void computeAddOutput(MCSimpleAdd *add)
  {
  Shift::FloatProperty::ComputeLock l(&add->output);

  *l.data() = add->inputA() + add->inputB();
  }

S_IMPLEMENT_PROPERTY(MCSimpleAdd, MathsCore)

void MCSimpleAdd::createTypeInformation(Shift::PropertyInformationTyped<MCSimpleAdd> *info,
                                        const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->child(&MCSimpleAdd::output);
    outInst->setCompute<computeAddOutput>();
    }
  }

void computeSubOutput(MCSimpleSubtract *add)
  {
  Shift::FloatProperty::ComputeLock l(&add->output);

  *l.data() = add->inputA() - add->inputB();
  }

S_IMPLEMENT_PROPERTY(MCSimpleSubtract, MathsCore)

void MCSimpleSubtract::createTypeInformation(Shift::PropertyInformationTyped<MCSimpleSubtract> *info,
                                        const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->child(&MCSimpleSubtract::output);
    outInst->setCompute<computeSubOutput>();
    }
  }
