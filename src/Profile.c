#include "common.h"

typedef struct _Profile {
  u32 mileage; // 10倍されている
} Profile;

static Profile* _profile;





Profile* ProfileGet() {
  // @todo 本来は保存したり読み直したりする
  if (_profile == NULL) {
    _profile = calloc(1, sizeof(Profile));
  }
  return _profile;
}
