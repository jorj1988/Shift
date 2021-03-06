#ifndef SHANDLER_H
#define SHANDLER_H

#include "shift/sglobal.h"
#include "shift/TypeInformation/sinterface.h"
#include <mutex>

namespace Eks
{
class TemporaryAllocatorCore;
}

namespace Shift
{

class Container;
class Database;
class Change;


class SHIFT_EXPORT Handler : public InterfaceBase
  {
  S_INTERFACE_TYPE(HandlerInterface)

XProperties:
  XWOProperty(Database *, database, setDatabase);
  XROProperty(xsize, revision)

public:
  Handler(bool stateStorageEnabled=true);
  ~Handler();

  void clearChanges();
  void clearUndo();

  static Handler *findHandler(Container *parent, Entity *prop);

  void beginBlock();
  void endBlock(bool cancel = false);


  Database *database() { xAssert(_database); return _database; }
  const Database *database() const { xAssert(_database); return _database; }

#ifdef X_CPPOX_SUPPORT
  template <typename CLS, typename... CLSARGS> void doChange(CLSARGS&&... params);
#else
  template <typename CLS, typename T0> void doChange(const T0 &t0);
  template <typename CLS, typename T0, typename T1> void doChange(const T0 &t0, const T1 &t1);
  template <typename CLS, typename T0, typename T1, typename T2> void doChange(const T0 &t0, const T1 &t1, const T2 &t2);
  template <typename CLS, typename T0, typename T1, typename T2, typename T3> void doChange(const T0 &t0, const T1 &t1, const T2 &t2, const T3 &t3);
#endif

  Eks::Vector<Observer *> &currentBlockObserverList() { return _blockObservers; }

  Eks::TemporaryAllocatorCore *temporaryAllocator() const;
  Eks::AllocatorBase *persistentBlockAllocator() const;
  Eks::AllocatorBase *generalPurposeAllocator() const;

  bool stateStorageEnabled() const { return _stateStorageEnabled; }
  void setStateStorageEnabled(bool enable) { _stateStorageEnabled = enable; }

  bool revisionsEnabled() const { return _changeIncrease == 1; }
  void setRevisionsEnabled(bool enable) { _changeIncrease = enable ? 1 : 0; }

private:
  Eks::AllocatorBase *changeAllocator();

  xuint32 _blockLevel;
  xuint32 _blockChangeCount;
  xuint8 _changeIncrease;

  void undoTo(xsize p);

  void onChangeComplete();
  Eks::Vector<Observer *> _blockObservers;
  std::mutex _doChange;

  Eks::Vector <Change*> _done;
  Eks::Vector <xsize> _blockSize;

  bool _stateStorageEnabled;
  };

class SHIFT_EXPORT Block
  {
public:
  Block(Handler *
#ifdef S_CENTRAL_CHANGE_HANDLER
    db
#endif
    )
#ifdef S_CENTRAL_CHANGE_HANDLER
    : _db(db)
#endif
    {
#ifdef S_CENTRAL_CHANGE_HANDLER
    xAssert(_db);
    _db->beginBlock();
#endif
    }

  ~Block()
    {
#ifdef S_CENTRAL_CHANGE_HANDLER
    _db->endBlock();
#endif
    }

private:
#ifdef S_CENTRAL_CHANGE_HANDLER
  Handler *_db;
#endif
  };

class SHIFT_EXPORT StateStorageBlock
  {
public:
  StateStorageBlock(bool enable, Handler *h)
#ifdef S_CENTRAL_CHANGE_HANDLER
    : _handler(h), _oldValue(h->stateStorageEnabled())
#endif
    {
    (void)enable;
    (void)h;
#ifdef S_CENTRAL_CHANGE_HANDLER
    _handler->setStateStorageEnabled(enable);
#endif
    }

  ~StateStorageBlock()
    {
#ifdef S_CENTRAL_CHANGE_HANDLER
    _handler->setStateStorageEnabled(_oldValue);
#endif
    }

#ifdef S_CENTRAL_CHANGE_HANDLER
  bool wasEnabled() const { return _oldValue; }
private:
  Handler *_handler;
  bool _oldValue;
#endif
  };

class SHIFT_EXPORT RevisionHoldBlock
  {
public:
  RevisionHoldBlock(Handler *h);
  ~RevisionHoldBlock();

private:
  Handler *_handler;
  bool _old;
  };

}

#endif // SHANDLER_H
