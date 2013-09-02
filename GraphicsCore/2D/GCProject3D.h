#ifndef GCPROJECT3D_H
#define GCPROJECT3D_H

#include "3D/GCTransform.h"
#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "GCElement.h"
#include "3D/GCCamera.h"

class GRAPHICSCORE_EXPORT GCProject3D : public Shift::Entity
  {
  S_ENTITY(GCProject3D, Entity)

public:

  GCCameraPointer camera;
  TransformProperty targetTransform;

  Shift::FloatProperty xPosition;
  Shift::FloatProperty yPosition;
  Shift::BoolProperty validPosition;
  };

#endif // GCPROJECT3D_H
