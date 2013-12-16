#ifndef SSAVER_H
#define SSAVER_H

#include "shift/sglobal.h"
#include "shift/Serialisation/sattributeio.h"
#include "Memory/XTemporaryAllocator.h"
#include "Memory/XUniquePointer.h"

class QIODevice;

namespace Shift
{

class SHIFT_EXPORT Saver : public SaveVisitor::Visitor
  {
public:
  class WriteBlock
    {
  XProperties:
    XROProperty(Saver *, writer);
    XROProperty(QIODevice *, device);
    XROProperty(bool, writing);
    XROProperty(bool, written);

  public:
    ~WriteBlock();

  private:
    WriteBlock(Saver *w, QIODevice *device);
    WriteBlock* _oldWriteBlock;

    friend class Saver;
    };

  class SaveDataImpl : public SaveData
    {
  public:
    SaveDataImpl(Attribute *root, SaveVisitor::Visitor *visitor);
    ~SaveDataImpl();

    Attribute *currentRoot() const { return _root; }

  private:
    Attribute *_root;
    };

  class AttributeDataImpl : public AttributeData
    {
  public:
    AttributeDataImpl(SaveData *data, Attribute *attr);

    Attribute *attribute() const { return _attribute; }
    Eks::TemporaryAllocator* allocator() const { return &_attributeAllocator; }

    const Symbol &modeSymbol() X_OVERRIDE;
    const Symbol &inputSymbol() X_OVERRIDE;
    const Symbol &valueSymbol() X_OVERRIDE;

    Saver *saver() { return _saver; }

  private:
    mutable Eks::TemporaryAllocator _attributeAllocator;
    Attribute *_attribute;
    Saver* _saver;

    friend class Saver;
    };
  typedef SerialisationSymbol Symbol;

  class Visitor
    {
  public:
    class SaveData
      {
    public:
      SaveData(SaveVisitor::Visitor *visitor);

      SaveVisitor::Visitor* visitor() { return _visitor; }

    private:
      SaveVisitor::Visitor* _visitor;
      };

    class AttributeData : public AttributeSaver
      {
    public:
      AttributeData(SaveData *data);

      SaveData* visitor() { return _data; }

    private:
      SaveData* _data;
      };

    /// \brief Begin a write of a whole tree to the writer. Called once at beginning.
    virtual Eks::UniquePointer<SaveData> beginVisit(Attribute *root) = 0;

    /// \brief Begin a series of calls to [beginWriting] or [writeSingleValue], with named attributes.
    virtual void beginNamedChildren(Attribute *a) = 0;
    /// \brief End seried of calls to children with named attributes.
    virtual void endNamedChildren(Attribute *a) = 0;

    /// \brief Begin a series of calls to [beginWriting] or [writeSingleValue], with indexed attributes.
    virtual void beginIndexedChildren(Attribute *a) = 0;
    /// \brief End seried of calls to children with indexed attributes.
    virtual void endIndexedChildren(Attribute *a) = 0;

    /// \brief Begin writing an attribute, which ends when the destructor is called.
    virtual Eks::UniquePointer<AttributeData> beginAttribute(Attribute *a) = 0;
    };

  Saver();

  WriteBlock beginWriting(QIODevice *device);

protected:
  virtual const SerialisationSymbol &modeSymbol() = 0;
  virtual const SerialisationSymbol &inputSymbol() = 0;
  virtual const SerialisationSymbol &valueSymbol() = 0;

  Eks::TemporaryAllocator* saveAllocator() const { return &_saveAllocator; }

private:
  mutable Eks::TemporaryAllocator _saveAllocator;
  WriteBlock *_block;

  friend class WriteBlock;
  friend class SaveDataImpl;
  };

class SHIFT_EXPORT SaveVisitor
  {
public:
  void visit(Attribute *attr, bool includeRoot, Saver *receiver);
  };

}

#endif // SSAVER_H