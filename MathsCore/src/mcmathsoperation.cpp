#if 0

#include "mcmathsoperation.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "QImage"

S_IMPLEMENT_PROPERTY(MCMathsOperation, MathsCore)

void MCMathsOperation::createTypeInformation(Shift::PropertyInformationTyped<MCMathsOperation> *info,
                                             const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerInterfaces)
    {
    auto ifc = info->apiInterface();

    XScript::ClassDef<0,0,1> cls = {
      {
        ifc->method<bool (QString), &MCMathsOperation::saveResultToFile>("saveResultToFile")
      }
    };

    ifc->buildInterface(cls);
    }
  }

void MCMathsOperation::assign(const Attribute *f, Attribute *t)
  {
  MCProfileFunction
  MCMathsOperation *to = t->uncheckedCastTo<MCMathsOperation>();
  const MCMathsOperation *from = f->uncheckedCastTo<MCMathsOperation>();

  MCMathsOperation::ComputeLock l(to);
  l.data()->copy(from->value());
  }

QImage MCMathsOperation::asQImage(const Eks::VectorI2D &pt, xuint32 scale, xuint32 w, xuint32 h) const
  {
  MCProfileFunction
  Eigen::Array<Eigen::Matrix<xint8, 4, 1>, Eigen::Dynamic, Eigen::Dynamic> arr(w, h);
  XMathsResult result(value(), pt, scale, XMathsOperation::Byte, &arr);

  QImage::Format fmt = QImage::Format_ARGB32;

  QImage im(w, h, fmt);
  uchar *bits = im.bits();
  xAssert(im.bytesPerLine()/w == 4);
  for(xuint32 y = 0; y < h; ++y)
    {
    QRgb *scanline = (QRgb*)(bits + y * im.bytesPerLine());
    for(xuint32 x = 0; x < w; ++x)
      {
      xuint32 alpha = 255;
      /*if(channels == 4)
        {
        alpha = data[3];
        }*/

      const Eigen::Matrix<xint8, 4, 1> &data = arr(x, y);

      *scanline = qRgba(data(0), data(1), data(2), alpha);
      scanline++;
      }
    }

  return im;
  }

bool MCMathsOperation::saveResultToFile(QString)
  {
  xAssertFail();
  /*QImage im = asQImage();
  im.save(filename);*/
  return true;
  }

#endif
