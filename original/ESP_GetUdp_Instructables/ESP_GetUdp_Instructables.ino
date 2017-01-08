//#include <LEDMatrix.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define teensy Serial

//######### WiFi
const char* ssid = "name";
const char* password = "passwd";
IPAddress IP(0, 0, 0, 0);
IPAddress local;

int broadcast = 255;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
const int port = 4321;
WiFiUDP udp;

int pieper = 4;
#define PIEPER_ACTIVE false
#define PIEPER_ACTIVE_ONCE true
boolean firstRun = true;

int destPort = port;
IPAddress destIP = IP;


void setup() {
  teensy.begin(9600);
  if (PIEPER_ACTIVE || PIEPER_ACTIVE_ONCE) pinMode(pieper, OUTPUT);
  if (PIEPER_ACTIVE || PIEPER_ACTIVE_ONCE) digitalWrite(pieper, LOW);

  local = connectToHomeNetwork();

  teensy.println(local);

  udp.begin(port);

  teensy.setTimeout(80);
}//end setup

long t1 = millis();

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    destPort = udp.remotePort();
    destIP = udp.remoteIP();
    handleIncoming(readUdp());
  }

  if (teensy.available()) {
    String in = "";
    while (teensy.available()) {
      in += char(teensy.read());
      delay(10);
    }
    handleTeensy(in);
  }
}//end loop



void handleIncoming(String incoming) {
  teensy.print(incoming);
}//end handleIncoming()

void handleTeensy(String incoming) {
  sendUdp(destIP, destPort, incoming);
}//end void handleTeensy()


String readUdp() {
  if (PIEPER_ACTIVE) digitalWrite(pieper, HIGH);
  if (PIEPER_ACTIVE_ONCE && firstRun) digitalWrite(pieper, HIGH);

  udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
  String reply = String(packetBuffer);
  for (int i = 0; i < UDP_TX_PACKET_MAX_SIZE; i++) packetBuffer[i] = 0;

  if (PIEPER_ACTIVE || (PIEPER_ACTIVE_ONCE && firstRun)) delay(30);
  if (PIEPER_ACTIVE) digitalWrite(pieper, LOW);
  if (PIEPER_ACTIVE_ONCE && firstRun) digitalWrite(pieper, LOW);
  firstRun = false;
  return reply;
}//end String readUdp()

void sendUdp(int ip, String command) {
  udp.beginPacket(ip, port);
  udp.print(command);
  udp.endPacket();
}//end void sendUdp()

void sendUdp(IPAddress ip, int port, String command) {
  udp.beginPacket(ip, port);
  udp.print(command);
  udp.endPacket();
}//end void sendUdp()

IPAddress connectToHomeNetwork() {
  // Connect to WiFi network
  IPAddress ip;
  WiFi.begin(ssid, password);

  long t = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    if (millis() >= t + 8000)
    {
      ip = (0, 0, 0, 0);
      return ip;
    }
  }
  return WiFi.localIP();
}//end void connectToHomenetwork()

