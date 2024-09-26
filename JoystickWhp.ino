#include <WiFi.h>    
#include <HTTPClient.h>
#include <UrlEncode.h>

const char* ssid = "SSID";
const char* password = "PWD";

// +international_country_code + phone number
// Portugal +351, example: +351912345678
String phoneNumber = "+5000000";
String apiKey = "000";

const int joystickX = 34;
const int joystickY = 35;


void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int valueX = analogRead(joystickX);
  int valueY = analogRead(joystickY);

  const int threshold = 1000;

  if (valueX < 1024 - threshold) {
    sendMessage("Se movio a la izquierda");
    delay(1000);
  }
  else if (valueX > 1024 - threshold) {
    sendMessage("Se movio a la derecha");
    delay(1000);
  }

  if (valueY < 1024 - threshold) {
    sendMessage("Se movio arriba");
    delay(1000);
  }
  else if (valueY > 1024 -threshold) {
    sendMessage("Se movio para abajo");
    delay(1000);
  }

  delay(100);
}
