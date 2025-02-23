#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Pusher credentials (from your dashboard)
#define PUSHER_HOST "ws.pusherapp.com"
#define PUSHER_PORT 80
#define PUSHER_KEY "c2fb34fa880960a9e301"  // Your Pusher Key
#define PUSHER_CLUSTER "ap2"  // Your cluster (Asia Pacific, Mumbai)
#define PUSHER_CHANNEL "home-control"
#define PUSHER_EVENT "control-event"

// Relay pins
#define RELAY1 D1  // GPIO 5
#define RELAY2 D2  // GPIO 4
#define RELAY3 D3  // GPIO 0
#define RELAY4 D4  // GPIO 2

WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);

  // Initialize relay pins
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY1, HIGH); // Relays are active-low, HIGH = OFF
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.println(WiFi.localIP());

  // Connect to Pusher
  String path = "/app/" + String(PUSHER_KEY) + "?protocol=7&client=js&version=7.0.0&flash=false";
  webSocket.begin(PUSHER_HOST, PUSHER_PORT, path);
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000); // Auto-reconnect if disconnected
}

void loop() {
  webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("Connected to Pusher");
      // Subscribe to the channel
      String subscribeMsg = "{\"event\":\"pusher:subscribe\",\"data\":{\"channel\":\"" + String(PUSHER_CHANNEL) + "\"}}";
      webSocket.sendTXT(subscribeMsg);
      break;
    case WStype_TEXT:
      String message = String((char*)payload);
      Serial.println("Received: " + message);
      // Parse Pusher event
      if (message.indexOf(PUSHER_EVENT) != -1) {
        if (message.indexOf("1ON") != -1) digitalWrite(RELAY1, LOW);
        else if (message.indexOf("1OFF") != -1) digitalWrite(RELAY1, HIGH);
        else if (message.indexOf("2ON") != -1) digitalWrite(RELAY2, LOW);
        else if (message.indexOf("2OFF") != -1) digitalWrite(RELAY2, HIGH);
        else if (message.indexOf("3ON") != -1) digitalWrite(RELAY3, LOW);
        else if (message.indexOf("3OFF") != -1) digitalWrite(RELAY3, HIGH);
        else if (message.indexOf("4ON") != -1) digitalWrite(RELAY4, LOW);
        else if (message.indexOf("4OFF") != -1) digitalWrite(RELAY4, HIGH);
      }
      break;
    case WStype_DISCONNECTED:
      Serial.println("Disconnected from Pusher");
      break;
  }
}