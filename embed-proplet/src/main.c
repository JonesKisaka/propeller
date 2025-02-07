#include "mqtt_client.h"
#include "wifi_manager.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main);

#define WIFI_SSID "<YOUR_WIFI_SSID>"
#define WIFI_PSK "<YOUR_WIFI_PSK>"
#define PROPLET_ID "<YOUR_PROPLET_ID>"
#define PROPLET_PASSWORD "<YOUR_PROPLET_PASSWORD>"
#define CHANNEL_ID "<YOUR_CHANNEL_ID>"


const char *channel_id = CHANNEL_ID;

int main(void) {
  LOG_INF("Starting Proplet...");

  wifi_manager_init();

  wifi_manager_connect(WIFI_SSID, WIFI_PSK);

  mqtt_client_connect(PROPLET_ID, CHANNEL_ID);

  publish_discovery(PROPLET_ID, CHANNEL_ID);

  subscribe(CHANNEL_ID);

  while (1) {
    mqtt_client_process();

    if (mqtt_connected) {
      publish_alive_message(CHANNEL_ID);
    } else {
      LOG_WRN("MQTT client is not connected");
    }

    k_sleep(K_SECONDS(5));
  }
}
