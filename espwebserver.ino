#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "Your Ssid";  // Enter SSID here
const char* password = "Your pswd";  //Enter Password here

int motor1_en = D5;
int motor1_a  = D0;
int motor1_b  = D1;

int motor2_en = D6;
int motor2_a  = D2;
int motor2_b  = D3;

/* Put IP Address details */
//IPAddress local_ip(192,168,1,1);
//IPAddress gateway(192,168,1,1);
//IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);



void setup() {
  Serial.begin(115200);
  pinMode(motor1_en, OUTPUT);
  pinMode(motor1_a, OUTPUT);
  pinMode(motor1_b, OUTPUT);

  pinMode(motor2_en, OUTPUT);
  pinMode(motor2_a, OUTPUT);
  pinMode(motor2_b, OUTPUT);

  analogWrite(motor1_en, 512);
  analogWrite(motor2_en, 512);
  Stop_no();
  WiFi.hostname("ERobotics");
  WiFi.mode(WIFI_STA);

  //  WiFi.softAP(ssid, password);
  //  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.begin(ssid , password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected with IP ");
  Serial.println(WiFi.localIP());

  delay(100);


  server.on("/", handle_OnConnect);
  server.on("/forward", Forward);
  server.on("/reverse", Reverse);
  server.on("/left", Left);
  server.on("/right", Right);
  server.on("/stop", Stop);
  server.on("/forward_no", Forward_no);
  server.on("/reverse_no", Reverse_no);
  server.on("/left_no", Left_no);
  server.on("/right_no", Right_no);
  server.on("/stop_no", Stop_no);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  server.keepAlive(true);

}
void loop() {
  server.handleClient();
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.hostname("ERobotics");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid , password);
    Serial.print("Reconnecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("WiFi connected with IP ");
    Serial.println(WiFi.localIP());
  }

}

void handle_OnConnect() {
  Serial.println("Connected");
  server.send(200, "text/html", SendHTML());
  Stop_no();
}

void Forward() {
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, HIGH);
  Serial.println("forward");
  server.send(200, "text/html", SendHTML());
}
void Forward_no() {
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, HIGH);
  Serial.println("forward_no");
  server.send(204, "text/plain", " ");
}
void Reverse() {
  digitalWrite(motor1_a, HIGH);
  digitalWrite(motor1_b, LOW);
  digitalWrite(motor2_a, HIGH);
  digitalWrite(motor2_b, LOW);
  Serial.println("reverse");
  server.send(200, "text/html", SendHTML());
}
void Reverse_no() {
  digitalWrite(motor1_a, HIGH);
  digitalWrite(motor1_b, LOW);
  digitalWrite(motor2_a, HIGH);
  digitalWrite(motor2_b, LOW);
  Serial.println("reverse_no");
  server.send(204, "text/plain", " ");
}

void Right() {
  digitalWrite(motor1_a, HIGH);
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, HIGH);
  Serial.println("right");
  server.send(200, "text/html", SendHTML());
}
void Right_no() {
  digitalWrite(motor1_a, HIGH);
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, HIGH);
  Serial.println("right_no");
  server.send(204, "text/plain", " ");
}

void Left() {
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, HIGH);
  digitalWrite(motor2_b, HIGH);
  Serial.println("left");
  server.send(200, "text/html", SendHTML());
}
void Left_no() {
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, HIGH);
  digitalWrite(motor2_b, HIGH);
  Serial.println("left_no");
  server.send(204, "text/plain", " ");
}
void Stop() {
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, LOW);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, LOW);
  Serial.println("stop");
  server.send(200, "text/html", SendHTML());
}
void Stop_no() {
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, LOW);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, LOW);
  Serial.println("stop_no");
  server.send(204, "text/plain", " ");
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
