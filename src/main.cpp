#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

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
  String btn = server.arg("btn");     // e.g. /press?btn=play
  Serial.printf("button: %s\n", btn.c_str());
  // TODO: map btn -> MIDI / action
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
}

void loop() {
  server.handleClient();
}
