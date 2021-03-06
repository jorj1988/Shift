#ifndef GCCOMPOSETRANSFORM_H
#define GCCOMPOSETRANSFORM_H

#include "shift/sentity.h"
#include "GCGlobal.h"
#include "shift/Properties/sbaseproperties.h"
#include "Utilities/RCBaseProperties.h"

class GCComposeTransform : public Shift::Entity
  {
  S_ENTITY(GCComposeTransform, Entity)

public:
  Shift::Vector3DProperty rotationAxisIn;
  Shift::FloatProperty rotationAngleIn;

  Shift::Vector3DProperty translationIn;

  TransformProperty transformOut;
  };

#endif // GCCOMPOSETRANSFORM_H
