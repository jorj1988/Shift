#ifndef GCCOMPOSEVECTOR3_H
#define GCCOMPOSEVECTOR3_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"

class GRAPHICSCORE_EXPORT GCComposeVector3 : public Shift::Entity
  {
  S_ENTITY(GCComposeVector3, Entity, 0)

public:
  Shift::FloatProperty xIn;
  Shift::FloatProperty yIn;
  Shift::FloatProperty zIn;

  Shift::Vector3DProperty vectorOut;
  };

S_PROPERTY_INTERFACE(GCComposeVector3)

#endif // GCCOMPOSEVECTOR3_H
