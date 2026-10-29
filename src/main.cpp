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
    MIDI.noteOn(60, 127, 1);
    MIDI.noteOn(60, 0, 1);
  } else if (btn == "cue") {
    MIDI.noteOn(62, 127, 1);
    MIDI.noteOn(62, 0, 1);
  } else if (btn == "c1_1"){
    MIDI.noteOn(63, 127, 1);
    MIDI.noteOn(63, 0, 1);
  } else if (btn == "c1_2"){
    MIDI.noteOn(64, 127, 1);
    MIDI.noteOn(64, 0, 1);
  } else if (btn == "c1_3"){
    MIDI.noteOn(65, 127, 1);
    MIDI.noteOn(65, 0, 1);
  } else if (btn == "c1_4"){
    MIDI.noteOn(66, 127, 1);
    MIDI.noteOn(66, 0, 1);
  } else if (btn == "c1_5"){
    MIDI.noteOn(67, 127, 1);
    MIDI.noteOn(67, 0, 1);
  } else if (btn == "c1_6"){
    MIDI.noteOn(68, 127, 1);
    MIDI.noteOn(68, 0, 1);
  } else if (btn == "c1_7"){
    MIDI.noteOn(69, 127, 1);
    MIDI.noteOn(69, 0, 1);
  } else if (btn == "c1_8"){
    MIDI.noteOn(70, 127, 1);
    MIDI.noteOn(70, 0, 1);
  } else if (btn == "play2") {
    MIDI.noteOn(71, 127, 1);
    MIDI.noteOn(71, 0, 1);
  } else if (btn == "cue2") {
    MIDI.noteOn(72, 127, 1);
    MIDI.noteOn(72, 0, 1);
  } else if (btn == "c2_1"){
    MIDI.noteOn(73, 127, 1);
    MIDI.noteOn(73, 0, 1);
  } else if (btn == "c2_2"){
    MIDI.noteOn(74, 127, 1);
    MIDI.noteOn(74, 0, 1);
  } else if (btn == "c2_3"){
    MIDI.noteOn(75, 127, 1);
    MIDI.noteOn(75, 0, 1);
  } else if (btn == "c2_4"){
    MIDI.noteOn(76, 127, 1);
    MIDI.noteOn(76, 0, 1);
  } else if (btn == "c2_5"){
    MIDI.noteOn(77, 127, 1);
    MIDI.noteOn(77, 0, 1);
  } else if (btn == "c2_6"){
    MIDI.noteOn(78, 127, 1);
    MIDI.noteOn(78, 0, 1);
  } else if (btn == "c2_7"){
    MIDI.noteOn(79, 127, 1);
    MIDI.noteOn(79, 0, 1);
  } else if (btn == "c2_8"){
    MIDI.noteOn(80, 127, 1);
    MIDI.noteOn(80, 0, 1);
  } else if (btn == "s1_1"){
	  MIDI.noteOn(81, 127, 1);
	  MIDI.noteOn(81, 0, 1);
  }  else if (btn == "s1_2"){
	  MIDI.noteOn(82, 127, 1);
	  MIDI.noteOn(82, 0, 1);
  }  else if (btn == "s1_3"){
	  MIDI.noteOn(83, 127, 1);
	  MIDI.noteOn(83, 0, 1);
  }  else if (btn == "s1_4"){
	  MIDI.noteOn(84, 127, 1);
	  MIDI.noteOn(84, 0, 1);
  }  else if (btn == "s2_1"){
	  MIDI.noteOn(85, 127, 1);
	  MIDI.noteOn(85, 0, 1);
  }  else if (btn == "s1_2"){
	  MIDI.noteOn(86, 127, 1);
	  MIDI.noteOn(86, 0, 1);
  }  else if (btn == "s1_3"){
	  MIDI.noteOn(87, 127, 1);
	  MIDI.noteOn(87, 0, 1);
  }  else if (btn == "s1_4"){
	  MIDI.noteOn(88, 127, 1);
	  MIDI.noteOn(88, 0, 1);
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
