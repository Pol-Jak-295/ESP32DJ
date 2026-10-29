#include <Arduino.h>
#include <WiFi.h>
#include <USB.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <USBMIDI.h>

USBMIDI MIDI;

WebServer server(80);
const char *SSID = "ESP32DJ";
const char *PASS = "djcontroller";   // >= 8 chars

void handleRoot() {
  File f = LittleFS.open("/index.html", "r");
  if (!f) { server.send(500, "text/plain", "no index.html"); return; }
  server.streamFile(f, "text/html");
  f.close();
}

void handlePress() {
  String btn = server.arg("btn");

  if (btn == "play") {
    // Send Note On, note 60, velocity 127, channel 1
    MIDI.noteOn(60, 127, 1);
    // Or send Control Change: MIDI.sendControlChange(20, 127, 1);
  } else if (btn == "stop") {
    MIDI.noteOn(61, 127, 1);
  } else if (btn == "cue") {
    MIDI.noteOn(62, 127, 1);
  }

  server.send(200, "text/plain", "ok");
}


void setup() {
  Serial.begin(115200);
  LittleFS.begin(true);              // true = format on mount fail
  WiFi.softAP(SSID, PASS);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());   // 192.168.4.1

  server.on("/", handleRoot);
  server.on("/press", handlePress);
  server.onNotFound([]() { server.send(404, "text/plain", "not found"); });
  server.begin();

  MIDI.begin();
  USB.begin();
}

void loop() {
  server.handleClient();
}
