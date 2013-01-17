#ifndef MCSHAPE_H
#define MCSHAPE_H

#include "GCRenderable.h"
#include "MCGeometry.h"

class MCShape : public GCRenderable
  {
  S_ENTITY(MCShape, GCRenderable, 0)

public:
  MCShape();

  MCGeometry geometry;

  void render(Eks::Renderer *) const;

  virtual void intersect(const Eks::Line& line, Selector *);
  virtual void intersect(const Eks::Frustum& frus, Selector *);
  };

S_PROPERTY_INTERFACE(MCShape)

#endif // MCSHAPE_H
