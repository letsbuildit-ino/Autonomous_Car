#include <WiFi.h>
#include <WebServer.h>
#include <esp32cam.h>
 
const char* WIFI_SSID = "xyz"; // edit in it your wifi ssid and password !!
const char* WIFI_PASS = "xyz";

int pin1 = 2;
int pin2 = 14;
int pin3 = 15;
 
WebServer server(80);
 
 
static auto loRes = esp32cam::Resolution::find(320, 240);
static auto midRes = esp32cam::Resolution::find(350, 530);
static auto hiRes = esp32cam::Resolution::find(800, 600);
void serveJpg()
{
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));
 
  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}
 
void handleJpgLo()
{
  if (!esp32cam::Camera.changeResolution(loRes)) {
    Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgHi()
{
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}
 
void handleJpgMid()
{
  if (!esp32cam::Camera.changeResolution(midRes)) {
    Serial.println("SET-MID-RES FAIL");
  }
  serveJpg();
}
 
void forward(){
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  Serial.println("Forward");
  digitalWrite(pin1, HIGH);  
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
}
void right(){
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  Serial.println("Right");
  digitalWrite(pin1, LOW);  
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
}
void left(){
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  Serial.println("Left");
  digitalWrite(pin1, HIGH);  
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
}
void extremeright(){
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  Serial.println("Extreme Right");
  digitalWrite(pin1, LOW);  
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
}
void extremeleft(){
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  Serial.println("Extreme Left");
  digitalWrite(pin1, HIGH);  
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
}
void hold(){
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  Serial.println("Stop");
  digitalWrite(pin1, HIGH);  
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
}
void returnback(){
  WiFiClient client = server.client();
  client.println("HTTP/1.1 200 OK");
  Serial.println("Returnback");
  digitalWrite(pin1, LOW);  
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
}
 
void setup(){
  
  pinMode(pin3, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin1, OUTPUT);
  
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();
  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);
 
    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("  /cam-lo.jpg");
  Serial.println("  /cam-hi.jpg");
  Serial.println("  /cam-mid.jpg");
 
  server.on("/F", forward);
  server.on("/R", right);
  server.on("/L", left);
  server.on("/ER", extremeright);
  server.on("/EL", extremeleft);
  server.on("/S", hold);
  server.on("/X", returnback);
  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.on("/cam-mid.jpg", handleJpgMid);
 
  server.begin();
}
 
void loop()
{
  server.handleClient();
}
