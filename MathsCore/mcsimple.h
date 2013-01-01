#ifndef MCSIMPLE_H
#define MCSIMPLE_H

#include "mcglobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"

class MATHSCORE_EXPORT MCSimple : public Shift::Entity
  {
  S_ENTITY(MCSimple, Shift::Entity, 0)

public:
  MCSimple();

  Shift::FloatProperty inputA;
  Shift::FloatProperty inputB;

  Shift::FloatProperty output;
  };

S_PROPERTY_INTERFACE(MCSimple)

#endif // MCSIMPLE_H
