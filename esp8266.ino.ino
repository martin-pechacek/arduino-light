  #include <ESP8266WiFi.h>
  #include <ArduinoJson.h>

  const char* ssid = "UPCAEED29E";
  const char* password = "Y8msxtMeadp6";
   
  const char* host = ""; // Your domain/server 
  String path = ""; // Path to light.json on website 

  String currentLine = "";            // string for incoming serial data
  String currRates = "";
  boolean readingRates = false;       // is reading?
    
  void setup() {      
    Serial.begin(9600);

    delay(10);
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: " + WiFi.localIP().toString());
  }

  void loop() {
    Serial.println("IP address: " + WiFi.localIP().toString());
      
    delay(2000);
      
    Serial.print("connecting to ");
    Serial.println(host);
      
    WiFiClient client;
    const int httpPort = 80;
      
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    } else {
      Serial.println("connected"); 
    }

    client.print(String("GET ") + path + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: close\r\n\r\n");

    delay(750); // wait for server to respond

    // read response
    String section="header";
    
    while(client.available()){
      String line = client.readStringUntil('\r');
      char inChar = client.read();
      
      currentLine += inChar;
        
      if (inChar == '\n') {
        currentLine = "";
      }
  
      if (currentLine.endsWith("{")){
        readingRates = true;
      } else if (readingRates){
        if (!currentLine.endsWith("}")) { //'>' is our ending character
          currRates += inChar;
        } else {
          readingRates = false;
          if (currRates.indexOf("on") >= 0){
            //LED ON
            Serial.println('1');
          } else if (currRates.indexOf("off") >= 0){
            //LED OFF
            Serial.println('0');
          }
           
          currRates = "";
          client.stop();                   
        }    
      }
    }
    Serial.println("closing connection. ");
    Serial.println("\n");
  }
