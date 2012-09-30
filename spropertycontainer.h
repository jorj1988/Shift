#ifndef SPROPERTYCONTAINER_H
#define SPROPERTYCONTAINER_H

#include "sglobal.h"
#include "sproperty.h"
#include "schange.h"

class SPropertyContainer;
class SPropertyInstanceInformationInitialiser;

#define S_PROPERTY_CONTAINER S_PROPERTY
#define S_ABSTRACT_PROPERTY_CONTAINER S_ABSTRACT_PROPERTY

#define S_COMPUTE_GROUP(name) static SProperty SPropertyContainer::* name[] = {
#define S_AFFECTS(property) reinterpret_cast<SProperty SPropertyContainer::*>(&className :: property),
#define S_COMPUTE_GROUP_END() 0 };


template <typename T, typename Cont> class SPropertyContainerBaseIterator;
template <typename T, typename Cont> class SPropertyContainerIterator;
template <typename T, typename Cont, typename Iterator> class SPropertyContainerTypedIteratorWrapperFrom;

class SHIFT_EXPORT SPropertyContainer : public SProperty
  {
  S_PROPERTY_CONTAINER(SPropertyContainer, SProperty, 0);

public:
  class TreeChange : public SChange
    {
    S_CHANGE(TreeChange, SChange, 52)
  public:
    TreeChange(SPropertyContainer *b, SPropertyContainer *a, SProperty *ent, xsize index);
    ~TreeChange();
    SPropertyContainer *before(bool back=false)
      {
      if(back)
        {
        return _after;
        }
      return _before;
      }
    const SPropertyContainer *before(bool back=false) const
      {
      if(back)
        {
        return _after;
        }
      return _before;
      }
    SPropertyContainer *after(bool back=false)
      {
      if(back)
        {
        return _before;
        }
      return _after;
      }
    const SPropertyContainer *after(bool back=false) const
      {
      if(back)
        {
        return _before;
        }
      return _after;
      }

    SProperty *property() const {return _property;}
    xsize index() const { return _index; }

  private:
    SPropertyContainer *_before;
    SPropertyContainer *_after;
    SProperty *_property;
    xsize _index;
    bool _owner;
    bool apply();
    bool unApply();
    bool inform(bool back);
    };

  SPropertyContainer();
  ~SPropertyContainer();

  template <typename T> const T *firstDynamicChild() const
    {
    return ((SPropertyContainer*)this)->firstDynamicChild<T>();
    }

  template <typename T> T *firstDynamicChild()
    {
    SProperty *prop = firstDynamicChild();
    while(prop)
      {
      T *t = prop->castTo<T>();
      if(t)
        {
        return t;
        }
      prop = nextDynamicSibling(prop);
      }
    return 0;
    }

  SProperty *firstChild();
  const SProperty *firstChild() const;
  SProperty *lastChild();
  const SProperty *lastChild() const;

  void disconnectTree();

  SProperty *firstDynamicChild() { preGet(); return _dynamicChild; }
  const SProperty *firstDynamicChild() const { preGet(); return _dynamicChild; }

  template <typename T> const T *nextDynamicSibling(const T *old) const
    {
    return ((SPropertyContainer*)this)->nextDynamicSibling<T>((T*)old);
    }

  template <typename T> T *nextDynamicSibling(const T *old)
    {
    SProperty *prop = nextDynamicSibling((const SProperty*)old);
    while(prop)
      {
      T *t = prop->castTo<T>();
      if(t)
        {
        return t;
        }
      prop = nextDynamicSibling((const SProperty*)prop);
      }
    return 0;
    }

  SProperty *nextDynamicSibling(const SProperty *p);
  const SProperty *nextDynamicSibling(const SProperty *p) const;

  template <typename T> const T *findChild(const QString &name) const
    {
    const SProperty *prop = findChild(name);
    if(prop)
      {
      return prop->castTo<T>();
      }
    return 0;
    }

  template <typename T> T *findChild(const QString &name)
    {
    SProperty *prop = findChild(name);
    if(prop)
      {
      return prop->castTo<T>();
      }
    return 0;
    }

  const SProperty *findChild(const QString &name) const;
  SProperty *findChild(const QString &name);

  bool isEmpty() const { return _containedProperties != 0; }

  xsize size() const;
  xsize containedProperties() const { return _containedProperties; }

  SProperty *at(xsize i);
  const SProperty *at(xsize i) const;

  // move a property from this to newParent
  void moveProperty(SPropertyContainer *newParent, SProperty *property);

  bool contains(const SProperty *) const;

  xsize index(const SProperty* prop) const;

  static void assignProperty(const SProperty *, SProperty *);
  static void saveProperty(const SProperty *, SSaver & );
  static SProperty *loadProperty(SPropertyContainer *, SLoader &);
  static bool shouldSavePropertyValue(const SProperty *);

  // iterator members, can be used like for (auto prop : container->walker())
  template <typename T> SPropertyContainerTypedIteratorWrapperFrom<T, SPropertyContainer, SPropertyContainerIterator<T, SPropertyContainer> > walker();
  template <typename T> SPropertyContainerTypedIteratorWrapperFrom<const T, const SPropertyContainer, SPropertyContainerIterator<const T, const SPropertyContainer> > walker() const;

  template <typename T> SPropertyContainerTypedIteratorWrapperFrom<T, SPropertyContainer, SPropertyContainerIterator<T, SPropertyContainer> > walkerFrom(T *);
  template <typename T> SPropertyContainerTypedIteratorWrapperFrom<const T, const SPropertyContainer, SPropertyContainerIterator<const T, const SPropertyContainer> > walkerFrom(const T *) const;

  template <typename T> SPropertyContainerTypedIteratorWrapperFrom<T, SPropertyContainer, SPropertyContainerIterator<T, SPropertyContainer> > walkerFrom(SProperty *);
  template <typename T> SPropertyContainerTypedIteratorWrapperFrom<const T, const SPropertyContainer, SPropertyContainerIterator<const T, const SPropertyContainer> > walkerFrom(const SProperty *) const;

  SPropertyContainerTypedIteratorWrapperFrom<SProperty, SPropertyContainer, SPropertyContainerBaseIterator<SProperty, SPropertyContainer> > walker();
  SPropertyContainerTypedIteratorWrapperFrom<const SProperty, const SPropertyContainer, SPropertyContainerBaseIterator<const SProperty, const SPropertyContainer> > walker() const;
  SPropertyContainerTypedIteratorWrapperFrom<SProperty, SPropertyContainer, SPropertyContainerBaseIterator<SProperty, SPropertyContainer> > walkerFrom(SProperty *prop);

  X_ALIGNED_OPERATOR_NEW

protected:
  // contained implies the property is aggregated by the inheriting class and should not be deleted.
  // you cannot add another contained property once dynamic properties have been added, this bool
  // should really be left alone and not exposed in sub classes
  SProperty *addProperty(const SPropertyInformation *info, xsize index=X_SIZE_SENTINEL, const QString& name=QString(), SPropertyInstanceInformationInitialiser *inst=0);
  void removeProperty(SProperty *);

  void clear();

  // remove and destroy all children. not for use by "array types", use clear instead.
  void internalClear(SDatabase *db);

private:
  SProperty *internalFindChild(const QString &name);
  const SProperty *internalFindChild(const QString &name) const;
  friend void setDependantsDirty(SProperty* prop, bool force);
  SProperty *_dynamicChild;
  xsize _containedProperties;
  SDatabase *_database;

  QString makeUniqueName(const QString &name) const;
  void internalInsertProperty(SProperty *, xsize index);
  void internalSetupProperty(SProperty *);
  void internalRemoveProperty(SProperty *);
  void internalUnsetupProperty(SProperty *);

  friend class TreeChange;
  friend class SEntity;
  friend class SProperty;
  friend class SDatabase;
  };

S_PROPERTY_INTERFACE(SPropertyContainer)

#endif // SPROPERTYCONTAINER_H
