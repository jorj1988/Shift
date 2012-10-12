#ifndef GCPLATE_H
#define GCPLATE_H

#include "3D/GCTransform.h"
#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "GCElement.h"
#include "3D/GCShadingGroup.h"

#include "XOptionalPointer"

class GRAPHICSCORE_EXPORT GCPlate : public GCElementArray
  {
  S_ENTITY(GCPlate, GCElementArray, 0)

  template <typename T> GCShadingGroup *addMaterial(T **matOut = 0)
    {
    XOptionalPointer<T> mat(matOut);

    GCShadingGroup* grp = addChild<GCShadingGroup>();
    renderGroup.addPointer(grp);

    mat = addChild<T>();
    grp->shader.setPointed(mat);

    return grp;
    }

  void render(XRenderer *) const X_OVERRIDE;
  };

S_PROPERTY_INTERFACE(GCPlate)

#endif // GCPLATE_H