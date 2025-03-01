#pragma once

#include "esphome.h"
#include "BLEDevice.h"

namespace esphome {
namespace bluetooth_broadcast {

class BluetoothBroadcast : public Component {
 public:
  BluetoothBroadcast()
      : send_count_(0), interval_(1000), current_count_(0), manufacturer_data_(""), is_broadcasting_(false) {}

  void set_send_count(int send_count) { send_count_ = send_count; }
  void set_interval(int interval) { interval_ = interval; }
  void set_manufacturer_data(const std::string &manufacturer_data) { manufacturer_data_ = manufacturer_data; }
  void start_broadcasting();
  void stop_broadcasting();

  void setup() override {
    if (is_broadcasting_) {
      startAdvertising();
    }
  }

  void loop() override {
    if (!is_broadcasting_) {
      return;
    }

    if (send_count_ > 0 && current_count_ >= send_count_) {
      stop_broadcasting();
      return;
    }

    if (millis() - last_broadcast_time_ >= interval_) {
      sendBluetoothBroadcast();
      last_broadcast_time_ = millis();
      current_count_++;
    }
  }

 private:
  void startAdvertising();
  void sendBluetoothBroadcast();

  int send_count_;
  int interval_;
  int current_count_;
  std::string manufacturer_data_;
  unsigned long last_broadcast_time_ = 0;
  bool is_broadcasting_;
};

}  // namespace bluetooth_broadcast
}  // namespace esphome
