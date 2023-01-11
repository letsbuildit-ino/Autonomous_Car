#include <WiFi.h>

const char* ssid = "DIGI_106918";
const char* password = "ddccef96";

void forward();
void backward();
void left();
void right();
void extremeleft();
void extremeright();
void stop();
void returnback();

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(15, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(2, OUTPUT);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
int value = 0;
}
void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/F\">here</a> for forward.<br>");
            client.print("Click <a href=\"/B\">here</a> for backward.<br>");
            client.print("Click <a href=\"/L\">here</a> for left.<br>");
            client.print("Click <a href=\"/R\">here</a> for right.<br>");
            client.print("Click <a href=\"/EL\">here</a> for extreme left.<br>");
            client.print("Click <a href=\"/ER\">here</a> for extreme right.<br>");
            client.print("Click <a href=\"/S\">here</a> for stop.<br>");
            client.print("Click <a href=\"/X\">here</a> for return back.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /F")) {
          forward();
          Serial.println("forward");
        }
        if (currentLine.endsWith("GET /B")) {
          backward();
          Serial.println("backward");
        }
        if (currentLine.endsWith("GET /L")) {
          left();
          Serial.println("left");
        }
        if (currentLine.endsWith("GET /R")) {
          right();
          Serial.println("right");
        }
        if (currentLine.endsWith("GET /ER")) {
          extremeright();
          Serial.println("extreme right");
        }
        if (currentLine.endsWith("GET /EL")) {
          extremeleft();
          Serial.println("extreme left");
        }
        if (currentLine.endsWith("GET /S")) {
          stop();
          Serial.println("stop");
        }
        if (currentLine.endsWith("GET /X")) {
          returnback();
          Serial.println("return back");
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

void forward(){
  digitalWrite(2, HIGH);  
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);  
}

void backward(){
  digitalWrite(2, LOW);  
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);  
}
void left(){
  digitalWrite(2, HIGH);  
  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);  
}
void right(){
  digitalWrite(2, LOW);  
  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);  
}
void extremeleft(){
  digitalWrite(2, HIGH);  
  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);  
}
void extremeright(){
  digitalWrite(2, LOW);  
  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);  
}
void stop(){
  digitalWrite(2, HIGH);  
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);  
}
void returnback(){
  digitalWrite(2, LOW);  
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);  
}
