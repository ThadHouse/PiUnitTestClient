#pragma once

#include "llvm/DenseMap.h"
#include "CANController.h"
#include "support/mutex.h"
#include <atomic>
#include <thread>
#include "llvm/Twine.h"



class CANMap {
 public:
  CANMap() {};
  CANMap(const llvm::Twine& port);
  int start(const llvm::Twine& port);
  void stop();
  void putData(const CANData& data);
  bool getData(int32_t requestedId, CANData* data);


 private:
  void readThreadMain();

  CANController m_controller;
  llvm::DenseMap<int32_t, CANData> m_dataMap;
  wpi::mutex m_mapMutex;

  std::atomic_bool m_running;
  std::thread m_incomingThread;
};

CANMap& getCANMap();
