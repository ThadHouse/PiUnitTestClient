#include "ntcore.h"
#include "CANMap.h"

int main() {
  getCANMap();
  auto val = NT_GetDefaultInstance();
  (void)val;
}
