// NodeMCU 1.0 ESP8266 DCmotor controlled by an Android app

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* SSID = "ssid";
const char* PASSWORD = "password";
ESP8266WebServer server(80);

/* TODO: edit pin names and uses */
const int pinUP = D5;
const int pinDOWN = D6;
const int pinENA = D4;
const int connLED = LED_BUILTIN;

// Declare movement states
int movementState;
const int IDLE = 0;
const int UP = 1;
const int DOWN = 2;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  /* TODO: Edit GPIOs */
  pinMode(pinUP, OUTPUT);
  pinMode(pinDOWN, OUTPUT);
  pinMode(connLED, OUTPUT);
  pinMode(pinENA, OUTPUT);

  WiFi.begin(SSID, PASSWORD);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(SSID);

  
  int dotCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if(dotCount < 3) {
      Serial.print(".");
    }
    dotCount++;

    blinkLED();
  }

  IPAddress ip(192, 168, 1, 7);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(192, 168, 1, 1);
  WiFi.config(ip, gateway, subnet, dns);

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");  
  Serial.println(WiFi.localIP());
  
  Serial.print("Subnet mask: ");
  Serial.println(WiFi.subnetMask());

  Serial.print("Gateway IP address: ");
  Serial.println(WiFi.gatewayIP());

  Serial.print("DNS server IP address: ");
  Serial.println(WiFi.dnsIP());

  digitalWrite(connLED, LOW);

  // HTTP URL management
  server.on("/up", movementUP);
  server.on("/down", movementDOWN);
  server.on("/idle", movementIDLE);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("ESP8266 Server on port 80 Started");
}
void loop() {
  server.handleClient();

  reconnect();

  switch(movementState) {
    case UP:
      
      /* TODO: handle up state */
      digitalWrite(pinUP, HIGH);
      digitalWrite(pinDOWN, LOW);
      analogWrite(pinENA, 255);
      break;
    case DOWN:

      /* TODO: handle down state */
      digitalWrite(pinUP, LOW);
      digitalWrite(pinDOWN, HIGH);
      analogWrite(pinENA, 255);
      break;
    default:
      
      /* TODO: handle idle state */
      digitalWrite(pinUP, LOW);
      digitalWrite(pinDOWN, LOW);
      analogWrite(pinENA, 255);
      break;
  }
}

void movementIDLE() {

  /* TODO: handle movement idle */

  movementState = IDLE;
  Serial.println("LED: LOW, Movement: IDLE");
  server.send(200, "text/html", updateHTTP(movementState));
}

void movementUP() {

  /* TODO: handle movement up */

  movementState = UP;
  Serial.println("LED: green ON, Movement: UP");
  server.send(200, "text/html", updateHTTP(movementState));
}

void movementDOWN() {
  
  /* TODO: handle movement down */

  movementState = DOWN;
  Serial.println("LED: red ON, Movement: DOWN");
  server.send(200, "text/html", updateHTTP(movementState));
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String updateHTTP(int state){
  String tag = "<!DOCTYPE html> <html>\n";
  tag += "<head>\n";
  tag += "<title>ESP8266 Control</title>\n";
  tag += "</style>\n";
  tag += "</head>\n";
  tag += "<body>\n";
  
  switch(state) {
    case UP:
      tag += "<a href=\"/up\"></a>\n";
      break;
    case DOWN:
      tag += "<a href=\"/down\"></a>\n";
      break;
    default:
      tag += "<a href=\"/idle\"></a>\n";
      break;
  }

  tag += "</body>\n";
  tag += "</html>\n";
  return tag;
}

void blinkLED(){
  int brightness = 0;
  for (brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(connLED, brightness);
    delay(10);
  }

  for (brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(connLED, brightness);
    delay(10);
  }
}

void reconnect(){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    WiFi.disconnect();
    delay(1000);
    WiFi.begin(SSID, PASSWORD);

    int dotCount = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      if(dotCount < 3) {
        Serial.print(".");
      }
      dotCount++;

      blinkLED();
    }

    Serial.println();
    Serial.println("WiFi reconnected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    digitalWrite(connLED, LOW);
  }
}