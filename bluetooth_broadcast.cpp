#include "bluetooth_broadcast.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bluetooth_broadcast {

void BluetoothBroadcast::startAdvertising() {
  if (is_broadcasting_) {
    return;
  }

  BLEDevice::init("");
  pServer = BLEDevice::createServer();
  startAdvertising();
  is_broadcasting_ = true;
}

void BluetoothBroadcast::stop_broadcasting() {
  if (!is_broadcasting_) {
    return;
  }

  BLEDevice::deinit();
  is_broadcasting_ = false;
}

void BluetoothBroadcast::sendBluetoothBroadcast() {
  BLEAdvertisementData advertisementData;
  if (!manufacturer_data_.empty()) {
    std::vector<uint8_t> manufacturer_data_bytes;
    for (size_t i = 0; i < manufacturer_data_.length(); i += 2) {
      std::string byte_str = manufacturer_data_.substr(i, 2);
      uint8_t byte = (uint8_t)strtol(byte_str.c_str(), NULL, 16);
      manufacturer_data_bytes.push_back(byte);
    }
    advertisementData.addManufacturerData(manufacturer_data_bytes);
  }

  BLEDevice::getAdvertising()->setAdvertisementData(advertisementData);
  ESP_LOGD("BluetoothBroadcast", "Sending Bluetooth broadcast with Manufacturer Data: %s", manufacturer_data_.c_str());
}

}  // namespace bluetooth_broadcast
}  // namespace esphome
