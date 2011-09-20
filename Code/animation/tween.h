#ifndef AURORA_ANIMATION_TWEEN_H
#define AURORA_ANIMATION_TWEEN_H
#include <vector>
#include "tween_template.h"

namespace aurora {
namespace animation {

typedef float DefaultTimeType;
typedef TweenTemplate<float,DefaultTimeType> Tween;
typedef std::vector<Tween*> TweenVector;

}
}

#endif