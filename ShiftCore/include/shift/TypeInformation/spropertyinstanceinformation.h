#ifndef SPROPERTYINSTANCEINFORMATION_H
#define SPROPERTYINSTANCEINFORMATION_H

#include "shift/sglobal.h"
#include "shift/Utilities/spropertyname.h"

namespace Shift
{

class Property;
class PropertyContainer;
class PropertyInformation;
class PropertyInstanceInformation;
class EmbeddedPropertyInstanceInformation;
class DynamicPropertyInstanceInformation;

class PropertyInstanceInformationInitialiser
  {
public:
  virtual void initialise(PropertyInstanceInformation*) = 0;
  };

// Child information
class SHIFT_EXPORT PropertyInstanceInformation
  {
public:
  typedef void (*ComputeFunction)( const PropertyInstanceInformation *, PropertyContainer * );

  enum Mode
    {
    Internal,
    InputOutput,
    InternalInput,
    Input,
    Output,
    Computed,
    InternalComputed,
    UserSettable,

    NumberOfModes,

    Default = InputOutput
    };

XProperties:
  XProperty(const PropertyInformation *, childInformation, setChildInformation);
  XRefProperty(PropertyName, name);
  XProperty(xuint16, index, setIndex);
  XPropertyMember(xuint8, mode);
  XROProperty(xuint8, isDynamic);

public:
  PropertyInstanceInformation(bool dynamic);
  static void destroy(PropertyInstanceInformation *);

  void setInvalidIndex();

  Mode mode() const;
  void setMode(Mode);
  void setModeString(const Eks::String &);
  bool isDefaultMode() const;
  const Eks::String &modeString() const;

  const EmbeddedPropertyInstanceInformation* embeddedInfo() const;
  const DynamicPropertyInstanceInformation* dynamicInfo() const;

  X_ALIGNED_OPERATOR_NEW
  };

class SHIFT_EXPORT EmbeddedPropertyInstanceInformation : public PropertyInstanceInformation
  {
  // Static Instance Members
  XProperty(PropertyInformation *, holdingTypeInformation, setHoldingTypeInformation);
  XProperty(xuint16, location, setLocation);
  XROProperty(xint16, defaultInput);

  XROProperty(ComputeFunction, compute);
  XROProperty(xsize *, affects);

  XProperty(bool, isExtraClassMember, setIsExtraClassMember);

public:
  EmbeddedPropertyInstanceInformation();

  static EmbeddedPropertyInstanceInformation *allocate(xsize size);

  void setMode(Mode);

  const EmbeddedPropertyInstanceInformation *resolvePath(const Eks::String &) const;

  virtual void setDefaultValue(const QString &);
  virtual void initiateProperty(Property *propertyToInitiate) const;

  Property *locateProperty(PropertyContainer *parent) const;
  const Property *locateProperty(const PropertyContainer *parent) const;

  const PropertyContainer *locateConstParent(const Property *prop) const;
  PropertyContainer *locateParent(Property *prop) const;

  void setCompute(ComputeFunction fn);
  bool isComputed() const { return _compute != 0; }

  void addAffects(const EmbeddedPropertyInstanceInformation *info);
  void setAffects(const EmbeddedPropertyInstanceInformation *info);
  void setAffects(const EmbeddedPropertyInstanceInformation **info, xsize size);
  void setAffects(xsize *affects);
  bool affectsSiblings() const { return _affects != 0; }

  void initiate(const PropertyInformation *info,
                const QString &name,
                xsize index,
                xsize s);

  void setDefaultInput(const EmbeddedPropertyInstanceInformation *info);
  };

class SHIFT_EXPORT DynamicPropertyInstanceInformation : public PropertyInstanceInformation
  {
  // Dynamic Instance
  XProperty(PropertyContainer *, parent, setParent)
  XProperty(Property *, nextSibling, setNextSibling)

public:
  DynamicPropertyInstanceInformation();
  };

inline const EmbeddedPropertyInstanceInformation* PropertyInstanceInformation::embeddedInfo() const
  {
  xAssert(!isDynamic());
  return static_cast<const EmbeddedPropertyInstanceInformation*>(this);
  }

inline const DynamicPropertyInstanceInformation* PropertyInstanceInformation::dynamicInfo() const
  {
  xAssert(isDynamic());
  return static_cast<const DynamicPropertyInstanceInformation*>(this);
  }

}

#endif // SPROPERTYINSTANCEINFORMATION_H
