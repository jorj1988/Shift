#ifndef GCRENDERABLE_H
#define GCRENDERABLE_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "GCBaseProperties.h"

class XRenderer;
class XLine;
class XFrustum;

class GRAPHICSCORE_EXPORT GCRenderable : public Shift::Entity
  {
  S_ABSTRACT_ENTITY(GCRenderable, Entity, 0)

public:
  GCRenderable();

  GCBoundingBox bounds;

  virtual void render(XRenderer *) const = 0;

  class Selector
    {
  public:
    virtual void onHit(const Eks::Vector3D &point, const Eks::Vector3D& normal, GCRenderable *renderable) = 0;
    };

  virtual void intersect(const XLine &line, Selector *);
  virtual void intersect(const XFrustum &frus, Selector *);
  };

S_PROPERTY_INTERFACE(GCRenderable)
S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCRenderablePointer, GCRenderable)
S_TYPED_POINTER_ARRAY_TYPE(GRAPHICSCORE_EXPORT, GCRenderablePointerArray, GCRenderablePointer)

class GRAPHICSCORE_EXPORT GCRenderArray : public GCRenderable
  {
  S_ENTITY(GCRenderArray, GCRenderable, 0)

public:
  GCRenderArray();

  GCRenderablePointerArray renderGroup;

  virtual void render(XRenderer *) const;

  virtual void intersect(const XLine &line, Selector *);
  virtual void intersect(const XFrustum &frus, Selector *);
  };

S_PROPERTY_INTERFACE(GCRenderArray)
S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCRenderArrayPointer, GCRenderArray)

#endif // GCRENDERABLE_H
