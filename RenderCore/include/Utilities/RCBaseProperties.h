#ifndef RCBASEPROPERTIES_H
#define RCBASEPROPERTIES_H

#include "RCGlobal.h"
#include "Math/XMathVector.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XTransform.h"
#include "QtGui/QImage"
#include "XShader.h"
#include "XGeometry.h"
#include "XRasteriserState.h"
#include "XBoundingBox.h"

namespace Eks
{
RENDERCORE_EXPORT std::ostream &operator<<(std::ostream &s, Eks::Renderer *);
RENDERCORE_EXPORT std::istream &operator>>(std::istream &s, Eks::Renderer *);
}

namespace GraphicsCore
{
namespace detail
{

class ShaderInstance
  {
public:
  ShaderInstance() : instance(0) { }
  Eks::Shader *instance;

  bool operator !=(const ShaderInstance& i) const
    {
    return i.instance != instance;
    }
  };
}

}

#if X_QT_INTEROP

Q_DECLARE_METATYPE(GraphicsCore::detail::ShaderInstance)

#endif

struct RCVertexLayoutWrapper
  {
  const Eks::ShaderVertexLayoutDescription *layout;
  xsize layoutCount;
  };

typedef Shift::Data<Eks::Shader, Shift::ComputedData>
  RCRuntimeShader;
typedef Shift::Data<Eks::ShaderConstantData, Shift::ComputedData>
  RCShaderRuntimeConstantData;
typedef Shift::Data<GraphicsCore::detail::ShaderInstance, Shift::ComputedData>
  RCRuntimeShaderInstance;
typedef Shift::Data<Eks::RasteriserState, Shift::ComputedData>
  RCRuntimeRasteriserState;
typedef Shift::Data<Eks::Geometry, Shift::ComputedData>
  RCRuntimeGeometry;
typedef Shift::Data<Eks::IndexGeometry, Shift::ComputedData>
  RCRuntimeIndexGeometry;
typedef Shift::Data<RCVertexLayoutWrapper, Shift::ComputedData>
  RCVertexLayout;
typedef Shift::Data<Eks::Renderer *>
  RCRenderer;
typedef Shift::Data<Eks::Transform>
  TransformProperty;
typedef Shift::Data<Eks::Matrix3x3>
  Matrix3x3Property;
typedef Shift::Data<Eks::ComplexTransform>
  ComplexTransformProperty;
typedef Shift::Data<Eks::BoundingBox>
  RCBoundingBox;

namespace Shift
{
namespace detail
{
RENDERCORE_EXPORT void getDefault(Eks::Transform *);
RENDERCORE_EXPORT void getDefault(Eks::Renderer **);
RENDERCORE_EXPORT void getDefault(Eks::Matrix3x3 *);

RENDERCORE_EXPORT void assignTo(const Shift::Attribute *f, Matrix3x3Property *to);
RENDERCORE_EXPORT void assignTo(const Shift::Attribute *f, TransformProperty *to);
RENDERCORE_EXPORT void assignTo(const Shift::Attribute *f, ComplexTransformProperty *to);
RENDERCORE_EXPORT void assignTo(const Shift::Attribute *f, Shift::Data<Eks::Renderer *> *to);
RENDERCORE_EXPORT void assignTo(const Shift::Attribute *f, RCBoundingBox *to);
}
}

S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCVertexLayoutPointer, RCVertexLayout)

S_DECLARE_METATYPE(TransformProperty, "TransformProperty");
S_DECLARE_METATYPE(ComplexTransformProperty, "ComplexTransformProperty");
S_DECLARE_METATYPE(Matrix3x3Property, "Matrix3x3Property");
S_DECLARE_METATYPE(RCRuntimeShader, "RuntimeShader");
S_DECLARE_METATYPE(RCRuntimeShaderInstance, "RuntimeShaderInstance");
S_DECLARE_METATYPE(RCShaderRuntimeConstantData, "ShaderRuntimeConstantData");
S_DECLARE_METATYPE(RCRuntimeRasteriserState, "RuntimeRasteriserState");
S_DECLARE_METATYPE(RCVertexLayout, "VertexLayout");
S_DECLARE_METATYPE(RCRenderer, "Renderer");
S_DECLARE_METATYPE(RCBoundingBox, "BoundingBox");
S_DECLARE_METATYPE(RCRuntimeIndexGeometry, "IndexGeometry");
S_DECLARE_METATYPE(RCRuntimeGeometry, "Geometry");

#endif // RCBASEPROPERTIES_H
