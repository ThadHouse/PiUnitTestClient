#include "PDP.h"
#include <chrono>

int PDP::start() {
  m_running = true;
  m_writeThread = std::thread(&PDP::writeThreadMain, this);
  return 0;
}

void PDP::stop() {
  m_running = false;

  if (m_writeThread.joinable()) m_writeThread.join();
}

void PDP::writeThreadMain() {
  auto sleepTime = std::chrono::steady_clock::now();
  while (m_running) {
    // TODO:: combine everything
    sleepTime += std::chrono::milliseconds(25);
    std::this_thread::sleep_until(sleepTime);
  }
}
