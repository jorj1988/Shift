#include "sexternalpointer.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Serialisation/sattributeio.h"
#include "shift/Properties/sdata.inl"
#include "Utilities/XOptional.h"


namespace Shift
{

ExternalPointerInstanceInformation::ExternalPointerInstanceInformation()
    : _resolveFunction(0)
  {
  }

S_IMPLEMENT_PROPERTY(ExternalPointer, Shift)

void ExternalPointer::createTypeInformation(PropertyInformationTyped<ExternalPointer> *,
                                            const PropertyInformationCreateData &)
  {
  }

Property *ExternalPointer::resolve(ResolveResult *resultOpt)
  {
  Property *inp = input();
  if(inp)
    {
    return inp;
    }

  const EmbeddedInstanceInformation *inst = embeddedInstanceInformation();
  EmbeddedInstanceInformation::ResolveExternalPointer resFn = inst->resolveFunction();
  xAssert(resFn);

  const Property *prop = resFn(this, inst, resultOpt);
  Shift::RevisionHoldBlock b(handler());
  setInput(prop);

  return input();
  }

const Property *ExternalPointer::resolve(ResolveResult *resultOpt) const
  {
  const Property *inp = input();
  if(inp)
    {
    return inp;
    }

  const EmbeddedInstanceInformation *inst = embeddedInstanceInformation();
  EmbeddedInstanceInformation::ResolveExternalPointer resFn = inst->resolveFunction();
  xAssert(resFn);

  const Property *prop = resFn(this, inst, resultOpt);
  return prop;
  }

class ExternalUuidPointer::Traits : public detail::PropertyBaseTraits
  {
public:
  static void save(const Attribute *p, AttributeSaver &s)
    {
    detail::PropertyBaseTraits::save(p, s, false);

    const ExternalUuidPointer *uuidProp = p->uncheckedCastTo<ExternalUuidPointer>();

    xAssert(!uuidProp->input() == uuidProp->_id.isNull());
    s.write(s.valueSymbol(), uuidProp->_id);
    }

  static Attribute *load(Container *parent, AttributeLoader &l)
    {
    Attribute *p = detail::PropertyBaseTraits::load(parent, l);

    Eks::TemporaryAllocator alloc(p->temporaryAllocator());

    ExternalUuidPointer *uuidProp = p->uncheckedCastTo<ExternalUuidPointer>();
    l.read(l.valueSymbol(), uuidProp->_id);

    return p;
    }
  };

S_IMPLEMENT_PROPERTY(ExternalUuidPointer, Shift)

void ExternalUuidPointer::createTypeInformation(PropertyInformationTyped<ExternalUuidPointer> *,
                                            const PropertyInformationCreateData &)
  {
  }

void ExternalUuidPointer::setPointed(const UuidEntity *entity)
  {
  _id = entity ? entity->_uuid() : QUuid();
  setInput(entity);
  }

S_IMPLEMENT_PROPERTY(UuidEntity, Shift)

void UuidEntity::createTypeInformation(PropertyInformationTyped<UuidEntity> *info,
                                            const PropertyInformationCreateData &data)
  {
  auto children = info->createChildrenBlock(data);

  children.add(&UuidEntity::_uuid, "uuid");
  }

void UuidEntity::setUuid(const QUuid &u)
  {
  _uuid = u;
  }
}
