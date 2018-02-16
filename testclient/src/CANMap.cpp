#include "CANMap.h"

int CANMap::start(const llvm::Twine& port) {
  m_running = true;
  m_incomingThread = std::thread(&CANMap::readThreadMain, this);
  return m_controller.start(port);
}

void CANMap::stop() {
  m_running = false;
  m_controller.stop();

  if (m_incomingThread.joinable()) m_incomingThread.join();
}

void CANMap::putData(const CANData& data) {
  m_controller.putData(data);
}

bool CANMap::getData(int32_t requestedId, CANData* data) {
  std::unique_lock<wpi::mutex> lock(m_mapMutex);
  auto i = m_dataMap.find(requestedId);
  if (i == m_dataMap.end()) return false;
  *data = i->second;
  return true;
}

void CANMap::readThreadMain() {
  while (m_running) {
    auto data = m_controller.getData();
    if (!m_running) break;

    std::unique_lock<wpi::mutex> lock(m_mapMutex);
    m_dataMap[data.id] = data;
  }
}

CANMap::CANMap(const llvm::Twine& port) {
  start(port);
}

CANMap& getCANMap() {
  static CANMap canMap("can0");
  return canMap;
}
