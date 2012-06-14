#ifndef MCIMAGE_H
#define MCIMAGE_H

#include "mcsource.h"
#include "sbaseproperties.h"

class MATHSCORE_EXPORT MCImage : public MCSource
  {
  S_ENTITY(MCImage, MCSource, 0);

public:
  MCImage();

  BoolProperty premultiply;
  StringProperty filename;

private:
  static void computeImageOutput(MCImage *image);
  XMathsOperation _preOperation;
  };

S_PROPERTY_INTERFACE(MCImage)

#endif // MCIMAGE_H
