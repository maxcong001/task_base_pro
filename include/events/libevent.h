#pragma once
#include <memory>

struct event_base;
extern "C" {
void event_base_free(event_base *);
}

struct evbuffer;
extern "C" {
void evbuffer_free(evbuffer *);
}

struct bufferevent;
extern "C" {
void bufferevent_free(bufferevent *);
}

struct evconnlistener;
extern "C" {
void evconnlistener_free(evconnlistener *);
}

/**
 * Global functionality specific to libevent.
 */
class Global
{
public:
  static bool initialized() { return initialized_; }

  /**
   * Initialize the library globally.
   */
  static void initialize();

private:
  // True if initialized() has been called.
  static bool initialized_;
};

/**
 * This is a helper that wraps C style API objects that need to be deleted with a smart pointer.
 */

template <class T, void (*deleter)(T *)>
class CSmartPtr : public std::unique_ptr<T, void (*)(T *)>
{
public:
  CSmartPtr() : std::unique_ptr<T, void (*)(T *)>(nullptr, deleter) {}
  CSmartPtr(T *object) : std::unique_ptr<T, void (*)(T *)>(object, deleter) {}
};

typedef CSmartPtr<event_base, event_base_free> BasePtr;
typedef CSmartPtr<evbuffer, evbuffer_free> BufferPtr;
typedef CSmartPtr<bufferevent, bufferevent_free> BufferEventPtr;
typedef CSmartPtr<evconnlistener, evconnlistener_free> ListenerPtr;
