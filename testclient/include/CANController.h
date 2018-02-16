#pragma once

#include <thread>
#include <atomic>
#include "llvm/Twine.h"
#include <support/ConcurrentQueue.h>

struct CANData {
  int32_t id;
  uint8_t length;
  uint8_t data[8];
};

class CANController {
public:
  int start(const llvm::Twine& port);
  void stop();
  CANData getData();
  void putData(const CANData& data);

  int getUtilPercent() { return m_utilPercent;}
private:
  void writeThreadMain();
  void readThreadMain();
  void utilThreadMain();


  std::atomic_bool m_running;
  wpi::ConcurrentQueue<CANData> m_incoming;
  wpi::ConcurrentQueue<CANData> m_outgoing;
  std::thread m_incomingThread;
  std::thread m_outgoingThread;
  std::thread m_utilThread;
  int m_socket {-1};

  std::atomic_int m_utilPercent {0};

  std::atomic_int m_totalBits {0};

};
