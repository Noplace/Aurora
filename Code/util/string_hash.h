#ifndef STRING_HASH_H
#define STRING_HASH_H

#include <ctype.h>

namespace core {

//typedef char* String; 

/*class Object {
 public:
  virtual ~Object();
  bool Equals(const Object other);
};

unsigned int HashDJB2(const char* str) {
  unsigned int hash = 0;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) ^ c;
  }

  return hash;
}*/

class StringHash {
 public:
  StringHash() {
    
  }

  StringHash(const char* str) {
    hash_ = ComputeHash(str);
  }

  static unsigned int ComputeHash(const char* str) {
    unsigned int hash_ = 0;
    int c;

    while (c = tolower(*str++)) {
      hash_ = ((hash_ << 5) + hash_) ^ c;
    }

    return hash_;
  }

  StringHash& operator =(const StringHash& other) {
    this->hash_ = other.hash_;
    return *this;
  }

  StringHash& operator =(const char* str) {
    this->hash_ = ComputeHash(str);
    return *this;
  }

  bool operator ==(const StringHash& other) const {
    return hash_ == other.hash_;
  }
  
  bool operator < (const StringHash& other) const {
    return hash_ < other.hash_;
  }

  unsigned int hash() { return hash_; }
  
 private:  
  unsigned int hash_;
};

}

#endif