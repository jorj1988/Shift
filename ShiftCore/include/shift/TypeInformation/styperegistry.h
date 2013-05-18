#ifndef STYPEREGISTRY_H
#define STYPEREGISTRY_H

#include "shift/sglobal.h"

namespace Eks
{
class TemporaryAllocatorCore;
}

namespace Shift
{

class NameArg;
class PropertyGroup;
class PropertyInformation;
class InterfaceBaseFactory;

class SHIFT_EXPORT TypeRegistry
  {
public:
  class Observer
    {
  public:
    virtual void typeAdded(const PropertyInformation *) = 0;
    virtual void typeRemoved(const PropertyInformation *) = 0;
    };

  static void addTypeObserver(Observer *o);
  static void removeTypeObserver(Observer *o);

  static void initiate(Eks::AllocatorBase *allocator);
  static void terminate();

  static Eks::AllocatorBase *persistentBlockAllocator();
  static Eks::AllocatorBase *generalPurposeAllocator();
  static Eks::AllocatorBase *interfaceAllocator();
  static Eks::TemporaryAllocatorCore *temporaryAllocator();

  static const Eks::Vector<const PropertyGroup *> &groups();
  static const Eks::Vector<const PropertyInformation *> &types();

  static void addPropertyGroup(PropertyGroup &);
  static void addType(PropertyInformation *);

  static const PropertyInformation *findType(const NameArg &);


  static const InterfaceBaseFactory *interfaceFactory(
      const PropertyInformation *info,
      xuint32 typeId);

  static void addInterfaceFactory(const PropertyInformation *info,
      xuint32 typeId,
      InterfaceBaseFactory *factory, xptrdiff offset);

private:
  TypeRegistry();
  X_DISABLE_COPY(TypeRegistry);

  static void internalAddType(PropertyInformation *);

  friend class PropertyGroup;
  };

}

#endif // STYPEREGISTRY_H
