//#include <LEDMatrix.h>
//#include <ESP8266WiFi.h>

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <WiFiUdp.h>

//for LED status
#include <Ticker.h>
Ticker ticker;

#define teensy Serial

//######### WiFi
//const char* ssid = "ssid name";
//const char* password = "enter_passwd";
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


void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}

void setup() {
  teensy.begin(9600);

  //set led pin as output
  pinMode(BUILTIN_LED, OUTPUT);
  // start ticker with 0.5 because we start in AP mode and try to connect
  ticker.attach(0.6, tick);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("ICROCO_CUBE_01")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  ticker.detach();
  //keep LED on
  digitalWrite(BUILTIN_LED, LOW);

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
  //  IPAddress ip;
  //  WiFi.begin(ssid, password);
  //
  //  long t = millis();
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(200);
  //    if (millis() >= t + 8000)
  //    {
  //      ip = (0, 0, 0, 0);
  //      return ip;
  //    }
  //  }
  return WiFi.localIP();
}//end void connectToHomenetwork()

