#include "shift/TypeInformation/smodule.h"
#include "shift/TypeInformation/spropertyinformation.h"
#include "shift/Properties/sattribute.inl"

namespace Shift
{

Module::Module()
    : _first(0)
  {
  }

void Module::install(Shift::ModuleBuilder *builder, Eks::AllocatorBase *alloc)
  {
  SProfileFunction

  _interfaces.allocator() = alloc;

  for(Information *i = _first; i; i = i->next)
    {
    i->bootstrap(alloc);

    xAssert(i->information);

    builder->addType(i->information);
    }
  
  initialiseInterfaces(*this);
    
  xForeach(const Module::InterfaceData &fac, interfaces())
    {
    builder->addInterfaceFactory(fac.type, fac.factory.get());
    }
  }

void Module::uninstall(Shift::ModuleBuilder *builder, Eks::AllocatorBase *alloc)
  {
  for(Information *i = _first; i; i = i->next)
    {
    auto info = i->information;
    xAssert(info);
    builder->removeType(info);
    PropertyInformation::destroyChildren(i->information, alloc);
    }

  for(Information *i = _first; i; i = i->next)
    {
    PropertyInformation::destroy(i->information, alloc);
    }

  xForeach(const Module::InterfaceData &fac, interfaces())
    {
    builder->removeInterfaceFactory(fac.type, fac.factory.get());
    }

  _interfaces.clear();
  _interfaces.squeeze();
  }

Module::Information &Module::registerPropertyInformation(Information &ths,
    BootstrapFunction bootstrapFunction)
  {
  Information *first = _first;
  _first = &ths;

  ths.information = nullptr;
  ths.bootstrap = bootstrapFunction;
  ths.next = first;
  return ths;
  }

}
