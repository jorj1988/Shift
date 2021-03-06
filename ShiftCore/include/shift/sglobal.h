#ifndef SGLOBAL_H
#define SGLOBAL_H

#include "XGlobal.h"

/** \mainpage Shift

    \version 0.5

    \section intro_sec Introduction

    Shift is a database/graph library for saving and loading and computing data.

    \section gettingstarted_sec Getting Started

    To start using shift, you need to create a Database, and some data!

    \sa Database
    \sa Entity
 */

#if defined(SHIFTCORE_BUILD)
#  define SHIFT_EXPORT X_DECL_EXPORT
#else
#  define SHIFT_EXPORT X_DECL_IMPORT
#endif

# define ShiftCoreProfileScope 1043
# define ShiftDataModelProfileScope 1044

#if X_EVENT_LOGGING_ENABLED
# include "XProfiler"
# define SProfileFunction X_EVENT_FUNCTION;
# define SProfileScopedBlock(mess) X_EVENT_FUNCTION;
#else
# define SProfileFunction
# define SProfileScopedBlock(mess)
#endif

#define S_DEFINE_USER_DATA_TYPE(name, typeId) namespace SUserDataTypes { static const xuint32 name = typeId; }
S_DEFINE_USER_DATA_TYPE(Invalid, 0)
S_DEFINE_USER_DATA_TYPE(InterfaceUserDataType, 0)

#define S_DEFINE_INTERFACE_TYPE(name, typeId) namespace SInterfaceTypes { static const xuint32 name = typeId; }
S_DEFINE_INTERFACE_TYPE(Invalid, 0)
S_DEFINE_INTERFACE_TYPE(PropertyVariantInterface, 1)
S_DEFINE_INTERFACE_TYPE(HandlerInterface, 2)
S_DEFINE_INTERFACE_TYPE(PropertyPositionInterface, 3)
S_DEFINE_INTERFACE_TYPE(PropertyColourInterface, 4)
S_DEFINE_INTERFACE_TYPE(PropertyConnectionInterface, 5)

#define S_MODULE_EXPORT shiftModule
#define S_MODULE_EXPORT_NAME "shiftModule"

#define S_MODULE_SIGNATURE Shift::Module &shiftModule()
#define S_MODULE(EXP, moduleName) namespace moduleName { EXP S_MODULE_SIGNATURE; }

#define S_IMPLEMENT_MODULE_EXPLICIT(moduleName, className) \
  namespace moduleName { S_MODULE_SIGNATURE { static className grp; return grp; } } \
  X_DECL_EXPORT extern "C" Shift::Module *S_MODULE_EXPORT() { return &moduleName::shiftModule(); }

#define S_IMPLEMENT_MODULE(moduleName) S_IMPLEMENT_MODULE_EXPLICIT(moduleName, Shift::Module)
#define S_IMPLEMENT_MODULE_WITH_INTERFACES(moduleName) \
  class moduleName##Module : public Shift::Module { virtual void initialiseInterfaces(Module &module) X_OVERRIDE; }; \
  S_IMPLEMENT_MODULE_EXPLICIT(moduleName, moduleName##Module) \
  void moduleName##Module::initialiseInterfaces(Module &module)

namespace Shift
{
class Entity;
class Attribute;
class Property;
class Observer;
class Module;

typedef Shift::Module *(*ModuleCSignature)();

enum DataMode
  {
  AttributeData,
  ComputedData,
  FullData,

  DataModeCount
  };

enum ChildModes
  {
  NoChildren = 0,

  AllowExtraChildren = 1,

  NamedChildren = 2,

  IndexedChildren = 4
  };

}

S_MODULE(SHIFT_EXPORT, Shift)

#endif // SHIFT_GLOBAL_H
