#include "shift/Serialisation/sbinaryio.h"
#include "shift/Properties/sattribute.inl"
#include "shift/sentity.h"
#include "shift/sdatabase.h"

namespace Shift
{

#if 0
SXMLLoader::SXMLLoader()
  {
  _buffer.open(QIODevice::ReadOnly);

  _childCount = "childCount";

  setStreamDevice(Text, &_buffer);
  }

void SXMLLoader::readFromDevice(QIODevice *device, Entity *parent)
  {
  _hasNextElement = false;
  _root = parent;

  _reader.setDevice(device);

  while (!_reader.atEnd())
    {
    findNext(false);

    if(_reader.isStartDocument())
      {
      findNext(false);
      xAssert(_reader.isStartElement());

      _currentAttributes = _reader.attributes();

      qDebug() << "name" << _currentAttributes.value("name");

      xsize count = childCount();
      for(xsize i=0; i<count; ++i)
        {
        beginNextChild();
        read(_root);
        endNextChild();
        }

      findNext(false);
      xAssert(_reader.isEndElement());
      findNext(false);
      xAssert(_reader.isEndDocument());
      }
    }

  if (_reader.hasError())
    {
    xAssertFail();
    }

  auto it = _resolveAfterLoad.begin();
  auto end = _resolveAfterLoad.end();
  for(; it != end; ++it)
    {
    Property *prop = it.key();
    Attribute* input = prop->resolvePath(it.value());

    xAssert(input);
    if(input)
      {
      input->connect(prop);
      }
    }

  _buffer.close();
  _root = 0;
  }


const PropertyInformation *SXMLLoader::type() const
  {
  xAssert(_root);

  const PropertyInformation *info = _root->handler()->findType(_typeName);
  xAssert(info);
  return info;
  }


xsize SXMLLoader::childCount() const
  {
  _scratch.clear();
  _currentAttributes.value(_childCount).appendTo(&_scratch);
  return _scratch.toULongLong();
  }

void SXMLLoader::beginNextChild()
  {
  findNext(false);
  xAssert(_reader.isStartElement());

  _typeName.clear();
  _reader.name().appendTo(&_typeName);
  _currentValue.clear();
  _currentAttributes = _reader.attributes();

  qDebug() << "name" << _currentAttributes.value("name");

  findNext(true);
  if(_reader.isCharacters())
    {
    _scratch.clear();
    _reader.text().appendTo(&_scratch);
    _currentValue = _scratch.toAscii();
    }
  else
    {
    _hasNextElement = true;
    xAssert(_reader.isEndElement() || _reader.isStartElement());
    }
  }

bool childHasValue() const
  {
  xAssertFail();
  return true;
  }

void SXMLLoader::endNextChild()
  {
  findNext(false);
  xAssert(_reader.isEndElement());
  _typeName.clear();
  }

void SXMLLoader::read(PropertyContainer *read)
  {
  _buffer.close();
  _buffer.setBuffer(&_currentValue);
  _buffer.open(QIODevice::ReadOnly);
  textStream().seek(0);

  const PropertyInformation *info = type();
  xAssert(info);

  xAssert(info->load());

  info->load()(read, *this);
  }

void SXMLLoader::beginAttribute(const char *attr)
  {
  xAssert(_currentAttributeValue.isEmpty());
  _scratch.clear();
  _currentAttributes.value(attr).appendTo(&_scratch);
  _currentAttributeValue = _scratch.toAscii();

  qDebug() << attr << _currentAttributes.value(attr) << _currentAttributeValue;

  _buffer.close();
  _buffer.setBuffer(&_currentAttributeValue);
  _buffer.open(QIODevice::ReadOnly);
  textStream().seek(0);
  }

void SXMLLoader::endAttribute(const char *attr)
  {
  _buffer.close();
  _buffer.setBuffer(&_currentValue);
  _buffer.open(QIODevice::ReadOnly);
  textStream().seek(0);

  _currentAttributeValue.clear();
  }

void SXMLLoader::resolveInputAfterLoad(Property *prop, const QString &path)
  {
  _resolveAfterLoad.insert(prop, path);
  }


bool SXMLLoader::isValidElement() const
  {
  return !_reader.isComment() && !_reader.isWhitespace();
  }

void SXMLLoader::findNext(bool allowWhitespace)
  {
  if(_hasNextElement && isValidElement())
    {
    _hasNextElement = false;

    if(allowWhitespace && _reader.isWhitespace())
      {
      xAssert(isValidElement() || (allowWhitespace && _reader.isWhitespace()));
      return;
      }
    else if(!allowWhitespace && !_reader.isWhitespace())
      {
      xAssert(isValidElement() || (allowWhitespace && _reader.isWhitespace()));
      return;
      }
    }

  do
    {
    _reader.readNext();
    } while(!isValidElement() && (!allowWhitespace && _reader.isWhitespace()));

  xAssert(isValidElement() || (allowWhitespace && _reader.isWhitespace()));
  }
#endif

}
