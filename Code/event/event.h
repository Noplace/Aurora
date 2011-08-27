#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>
#include <string.h>
#include "../util/string_hash.h"

namespace aurora {

class EventData {
 public:
  EventData() : time_stamp(0) {
  }
  uint64_t time_stamp;
};


class EventNullData : public EventData {
 public:
  EventNullData() : EventData() {
  }
};


typedef unsigned int EventHash;

class Event {
 public:
  Event(const char* name) : priority_(0), hash_(name) {
   strcpy_s(name_,name);
  }

  Event(const Event& other) {
    hash_ = other.hash_;
    strcpy_s(name_,other.name_);
  }

  Event operator= (const Event& other) {
    hash_ = other.hash_;
    strcpy_s(name_,other.name_);
    return *this;
  }

  bool operator== (const Event& other) const {
    return hash_ == other.hash_;
  }

  bool operator <(const Event& other) const {
    return priority_ < other.priority_;
  }

  const char* name() { return name_; }
  int priority() { return priority_; }
  EventHash hash() { return hash_.hash(); }
 private:
  core::StringHash hash_;
  char name_[64];
  int priority_;
};

}

#endif