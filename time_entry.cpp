#include "esphome.h"

class TimeEntryComponent : public Component, public CustomMQTTDevice {
 public:
  // Constructor
  TimeEntryComponent() : CustomMQTTDevice() {}

  void setup() override {
    // Subscribe to the MQTT topics for start and end times
    subscribe("homeassistant/switch/start_time/set", [this](const std::string& message) {
      this->onStartTimeSet(message);
    });
    subscribe("homeassistant/switch/end_time/set", [this](const std::string& message) {
      this->onEndTimeSet(message);
    });
  }

  void onStartTimeSet(const std::string& message) {
    // Parse the received message to extract the start time
    int hour = atoi(message.substr(0, 2).c_str());
    int minute = atoi(message.substr(3, 2).c_str());

    // Log the scheduled start time
    ESP_LOGI("TimeEntryComponent", "Work scheduled to start at %02d:%02d", hour, minute);

    // Trigger any actions here according to the scheduled start time
    // For example, you can turn on a relay, trigger a sensor, etc.
    // Example:
    // digitalWrite(RELAY_PIN, HIGH); // Turn on a relay
  }

  void onEndTimeSet(const std::string& message) {
    // Parse the received message to extract the end time
    int hour = atoi(message.substr(0, 2).c_str());
    int minute = atoi(message.substr(3, 2).c_str());

    // Log the scheduled end time
    ESP_LOGI("TimeEntryComponent", "Work scheduled to end at %02d:%02d", hour, minute);

    // Trigger any actions here according to the scheduled end time
    // For example, you can turn off a relay, reset a sensor, etc.
    // Example:
    // digitalWrite(RELAY_PIN, LOW); // Turn off a relay
  }
};

// Define a global instance of your custom component
TimeEntryComponent time_entry_component;
