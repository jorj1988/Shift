#ifndef GCSHADER_H
#define GCSHADER_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "shift/TypeInformation/sinterface.h"
#include "XShader.h"
#include "GCBaseProperties.h"

class GCShader;

class GCShaderInterface : public Shift::StaticInterfaceBase
  {
public:
  virtual bool initVertexShader(
    GCShader *,
    Eks::Renderer *,
    Eks::ShaderVertexComponent *,
    const Eks::ShaderVertexLayoutDescription *,
    xsize ,
    Eks::ShaderVertexLayout *) const
    { return false; }
  virtual bool initFragmentShader(
      GCShader *,
      Eks::Renderer *,
      Eks::ShaderFragmentComponent *) const
    { return false; }
  };

class GCShaderBindableData : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(GCShaderBindableData, GCShaderBindableInterface)
public:

  enum
    {
    DataSize = 128,
    ResourceCount = 4
    };
  typedef Eks::Vector<xuint8, DataSize> DataBlock;
  typedef Eks::Vector<const Eks::Resource *, ResourceCount> ResourceBlock;

  virtual void bindData(DataBlock *data, ResourceBlock *resources, const Shift::Property *) const = 0;
  };

class GRAPHICSCORE_EXPORT GCShader : public Shift::Entity
  {
  S_ENTITY(GCShader, Shift::Entity, 0)
public:

  void bind(Eks::Renderer *r) const;
  GCRuntimeShaderInstance runtimeShader;

  GCRenderer renderer;
  GCVertexLayoutPointer layoutDescription;

  GCRuntimeShader runtimeShaderCore;

protected:
  Eks::ShaderVertexLayout layout;

  Eks::ShaderConstantData constantData;
  GCShaderBindableData::ResourceBlock resources;

private:
  static void setupShaderRuntime(GCShader *cont);
  };

class GRAPHICSCORE_EXPORT GCStaticShader : public GCShader
  {
  S_ABSTRACT_ENTITY(GCStaticShader, GCShader, 0)

private:
  Eks::ShaderFragmentComponent fragment;
  Eks::ShaderVertexComponent vertex;

  static void computeShaderRuntime(GCStaticShader *cont);
  };

S_PROPERTY_INTERFACE(GCShader)
S_PROPERTY_INTERFACE(GCStaticShader)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShaderPointer, GCShader);

#endif // GCSHADER_H
