#ifndef GCMANIPULATOR_H
#define GCMANIPULATOR_H

#include "GCGlobal.h"
#include "shift/Properties/scontainer.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "GCBaseProperties.h"
#include "3D/GCCamera.h"
#include "XUniquePointer"

namespace Eks
{
class Renderer;
}

class QPainter;
class GCTransform;
class GCCamera;
class GCRenderable;
class GCRenderablePointerArray;
class GCViewableTransform;

class GRAPHICSCORE_EXPORT GCVisualManipulator : public Shift::Container
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualManipulator, Container, 0)

public:
  GCVisualManipulator();

  class Delegate
    {
  public:
    virtual ~Delegate() { }

    virtual bool hitTest(
      const GCVisualManipulator *toRender,
      const QPoint &widgetSpacePoint,
      const GCViewableTransform *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance) const = 0;

    virtual void render(const GCVisualManipulator *toRender,
                        const GCViewableTransform *camera,
                        Eks::Renderer *) const = 0;
    };

public:
  Shift::BoolProperty show;
  TransformProperty parentTransform;
  TransformProperty localTransform;
  TransformProperty worldTransform;

  virtual Eks::Transform resultTransform(const GCViewableTransform *tr) const;

  enum ScaleMode
    {
    ScreenSpaceScale,
    WorldSpaceScale,

    ScaleModeCount
    };
  typedef xuint32 ScaleType;

  static Eks::Transform computeScaledResultTransform(
      const Eks::Transform &worldTransform,
      ScaleType mode,
      const GCViewableTransform *scalePartnerTransform,
      float displayScale);


  Shift::EnumProperty scaleMode;
  Shift::FloatProperty displayScale;

  virtual Eks::Vector3D focalPoint(const GCViewableTransform *cam) const;

  virtual bool hitTest(
    const QPoint &widgetSpacePoint,
    const GCViewableTransform *camera,
    const Eks::Vector3D &clickDirection, // in world space
    float *distance,
    GCVisualManipulator **clicked);

  virtual void render(const GCCamera *camera, Eks::Renderer *) const;

  const Delegate *delegate() const;
  template <typename T> T *createDelegate()
    {
    _delegate = Shift::TypeRegistry::generalPurposeAllocator()->createUnique<T>();
    return static_cast<T*>(_delegate.pointer());
    }

  struct MouseEvent
    {
    QPoint widgetPoint;
    const GCViewableTransform *cam;
    Eks::Vector3D direction;
    };

  struct MouseMoveEvent : public MouseEvent
    {
    QPoint lastWidgetPoint;
    Eks::Vector3D lastDirection;
    };

  virtual void onMouseClick(const MouseEvent &) = 0;
  virtual void onMouseDoubleClick(const MouseEvent &) = 0;
  virtual void onMouseDrag(const MouseMoveEvent &) = 0;
  virtual void onMouseRelease(const MouseEvent &) = 0;

private:
  Eks::UniquePointer<Delegate> _delegate;
  };

class GRAPHICSCORE_EXPORT GCVisualCompoundManipulator : public GCVisualManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualCompoundManipulator, GCVisualManipulator, 0)

public:
  bool hitTest(
    const QPoint &widgetSpacePoint,
    const GCViewableTransform *camera,
    const Eks::Vector3D &clickDirection, // in world space
    float *distance,
    GCVisualManipulator **clicked) X_OVERRIDE;

  void render(const GCCamera *camera, Eks::Renderer *r) const X_OVERRIDE;

  void onMouseClick(const MouseEvent &) X_OVERRIDE;
  void onMouseDoubleClick(const MouseEvent &) X_OVERRIDE;
  void onMouseDrag(const MouseMoveEvent &) X_OVERRIDE;
  void onMouseRelease(const MouseEvent &) X_OVERRIDE;
  };

class GRAPHICSCORE_EXPORT GCVisualDragManipulator : public GCVisualManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualDragManipulator, GCVisualManipulator, 0)

public:
  virtual void onDrag(const MouseMoveEvent &) = 0;

  void onMouseClick(const MouseEvent &) X_OVERRIDE;
  void onMouseDoubleClick(const MouseEvent &) X_OVERRIDE;
  void onMouseDrag(const MouseMoveEvent &) X_OVERRIDE;
  void onMouseRelease(const MouseEvent &) X_OVERRIDE;
  };

class GRAPHICSCORE_EXPORT GCVisualClickManipulator : public GCVisualManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCVisualClickManipulator, GCVisualManipulator, 0)

public:
  virtual void onClick() = 0;

  void onMouseClick(const MouseEvent &) X_OVERRIDE;
  void onMouseDoubleClick(const MouseEvent &) X_OVERRIDE;
  void onMouseDrag(const MouseMoveEvent &) X_OVERRIDE;
  void onMouseRelease(const MouseEvent &) X_OVERRIDE;
  };

class GRAPHICSCORE_EXPORT GCDisplacementDragManipulator : public GCVisualDragManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCDisplacementDragManipulator, GCVisualDragManipulator, 0)

public:
  enum LockMode
    {
    Free,
    Planar,
    Linear
    };

  Shift::EnumProperty lockMode;
  Shift::Vector3DProperty lockDirection; // normal for planar, direction for linear, local space

  void onDrag(const MouseMoveEvent &, Eks::Vector3D &rel);
  };

class GRAPHICSCORE_EXPORT GCAngularDragManipulator : public GCVisualDragManipulator
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCAngularDragManipulator, GCVisualDragManipulator, 0)

public:
  enum LockMode
    {
    Free,
    Planar
    };

  Shift::EnumProperty lockMode;
  Shift::Vector3DProperty lockDirection; // normal for planar, direction for linear, local space

  void onDrag(const MouseMoveEvent &, Eks::Quaternion &rel);
  };

#endif // GCMANIPULATOR_H
