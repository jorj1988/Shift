#ifndef SCONTAINER_INL
#define SCONTAINER_INL

#include "shift/Properties/scontainer.h"

namespace Shift
{

class Container::EditCache
  {
XProperties:
  XROProperty(Container *, container)
  XROProperty(Database *, database)
  XROProperty(Eks::AllocatorBase *, allocator)

public:
  EditCache(Container *c, Eks::AllocatorBase *a);
  ~EditCache();

  void addChild(Attribute *a);
  void removeChild(Attribute *a);
  Attribute *findChild(const Name &n);

private:
  Eks::UnorderedMap<Name, Attribute *> _childMap;
  };

template <typename T> const T *Container::firstDynamicChild() const
  {
  return ((Container*)this)->firstDynamicChild<T>();
  }

template <typename T> T *Container::firstDynamicChild()
  {
  Attribute *prop = firstDynamicChild();
  while(prop)
    {
    T *t = prop->castTo<T>();
    if(t)
      {
      return t;
      }
    prop = nextDynamicSibling(prop);
    }
  return nullptr;
  }

template <typename T> const T *Container::firstChild() const
  {
  return ((Container*)this)->firstChild<T>();
  }

template <typename T> T *Container::firstChild()
  {
  xForeach(auto child, walker<T>())
    {
    return child;
    }
  return nullptr;
  }

Attribute *Container::firstDynamicChild()
  {
  preGet();
  return _dynamicChild;
  }

const Attribute *Container::firstDynamicChild() const
  {
  preGet();
  return _dynamicChild;
  }

Attribute *Container::lastDynamicChild()
  {
  preGet();
  return _lastDynamicChild;
  }

const Attribute *Container::lastDynamicChild() const
  {
  preGet();
  return _lastDynamicChild;
  }

template <typename T> const T *Container::nextDynamicSibling(const T *old) const
  {
  return ((Container*)this)->nextDynamicSibling<T>((T*)old);
  }

template <typename T> T *Container::nextDynamicSibling(const T *old)
  {
  Attribute *prop = nextDynamicSibling((const Attribute*)old);
  while(prop)
    {
    T *t = prop->castTo<T>();
    if(t)
      {
      return t;
      }
    prop = nextDynamicSibling((const Attribute*)prop);
    }
  return 0;
  }

template <typename T> T *Container::findChild(const NameArg &name)
  {
  Attribute *prop = findChild(name);
  if(prop)
    {
    return prop->castTo<T>();
    }
  return 0;
  }

template <typename T> const T *Container::findChild(const NameArg &name) const
  {
  const Attribute *prop = findChild(name);
  if(prop)
    {
    return prop->castTo<T>();
    }
  return 0;
  }

}

#endif // SCONTAINER_INL
