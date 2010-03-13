#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <muduo/base/UtcTime.h>
#include <muduo/net/TimerId.h>

namespace muduo
{
namespace net
{

class Channel;
class Poller;
class TimerQueue;

///
/// Reactor, at most one per thread.
///
class EventLoop : boost::noncopyable
{
 public:
  typedef boost::function<void()> TimerCallback;

  EventLoop();
  ~EventLoop();

  ///
  /// Loops forever.
  ///
  void loop();

  void quit();
  void wakeup();

  // timers
  TimerId runAt(const UtcTime& time, const TimerCallback& cb);
  TimerId runAfter(double delay, const TimerCallback& cb);
  TimerId runEvery(double interval, const TimerCallback& cb);
  void cancel(TimerId timerId);

  void addChannel(Channel* channel);
  void removeChannel(Channel* channel);

 private:
  void init();

  boost::scoped_ptr<Poller> poller_;
  boost::scoped_ptr<TimerQueue> timerQueue_;
  bool quit_; /* atomic */
};

}
}
#endif
