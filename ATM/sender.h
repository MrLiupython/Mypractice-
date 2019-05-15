#ifndef __SENDER_H_
#define __SENDER_H_

#include "squeue.h"

namespace messageing {
  class sender {
    queue* q;
   public:
    sender(): q(nullptr) {}
    
    explicit sender(queue* q_): q(q_) {}

    template<typename Message>
    void send(Message const& msg) {
      if(q) {
        q->push(msg);
      }
    }
  };
}
