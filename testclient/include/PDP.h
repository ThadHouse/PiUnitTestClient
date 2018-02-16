#pragma once

#include <thread>
#include <atomic>
#include "CANMap.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

class PDP {
 public:
  int start();
  void stop();
 private:
  void writeThreadMain();

  std::thread m_writeThread;
  CANMap& m_canMap = getCANMap();
};
