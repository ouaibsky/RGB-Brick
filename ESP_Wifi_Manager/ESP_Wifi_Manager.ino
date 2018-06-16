#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <WiFiUdp.h>

//for LED status
#include <Ticker.h>
Ticker ticker;

#define teensy Serial
// Change AP_NAME to avoid having twice equals on same network
#define AP_NAME "ICROCO_CUBE_06"
// Change udp port if you wanna listen/sent on something else
#define UDP_PORT 4321

//######### WiFi
WiFiUDP udp;
char incomingPacket[255];  // buffer for incoming packets

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
  wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect(AP_NAME)) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  ticker.detach();
  
  //keep LED on
  digitalWrite(BUILTIN_LED, HIGH);

  teensy.setTimeout(80);
  udp.begin(UDP_PORT);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), UDP_PORT);
}//end setup

long t1 = millis();

void loop() {
  int packetSize = udp.parsePacket();

  if (packetSize) {
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());
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
  sendUdp(udp.remoteIP(), udp.remotePort(), incoming);
}//end void handleTeensy()


String readUdp() {
  int len = udp.read(incomingPacket, UDP_TX_PACKET_MAX_SIZE);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
   Serial.printf("UDP packet contents: %s\n", incomingPacket);
   String reply = String(incomingPacket);

  return reply;
}//end String readUdp()

void sendUdp(int ip, String command) {
  udp.beginPacket(ip, UDP_PORT);
  udp.print(command);
  udp.endPacket();
}//end void sendUdp()

void sendUdp(IPAddress ip, int port, String command) {
  udp.beginPacket(ip, port);
  udp.print(command);
  udp.endPacket();
}//end void sendUdp()


