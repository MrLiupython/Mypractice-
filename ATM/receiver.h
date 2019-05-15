#ifndef __RECEIVER_H_
#define __RECEIVER_H_

#include "squeue.h"
#include "dispatcher.h"
namespace message {
  class receiver {
    queue q;
   public:
    operator sender() {
      return sender(&q);
    }
    dispatcher wait() {
      return dispatcher(&q);
    }
  };
}
