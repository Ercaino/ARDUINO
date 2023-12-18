/*
 * connect to the ESP8266 AP then
 * use web broswer to go to 192.168.4.1
 * 
 */
 
 
#include <ESP8266WiFi.h>
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "Wifi_AP_ESP8266" ;
 
WiFiServer server(80);
 
String request = "";
 
void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
 
    boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
    //WiFi.softAP(ssid, password, channel, hidden, max_connection)
    server.begin();
 
} 
 
void loop() 
{
 
    // Check if a client has connected
      WiFiClient client = server.available();
    if (!client) {
      return;
    }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    int value = LOW;
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(LED_BUILTIN, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(LED_BUILTIN, LOW);
    value = LOW;
  }
  
   
 
    // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
           
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #008CBA; border-radius: 12px; color: white; padding: 32px 16px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");
  
            
  client.println("<body><h1>Gruppo Esperti TPSIT</h1>");
  client.print("<h2>LO STATO DEL LED: </h2>");
 
  if(value == HIGH) {
    client.print("<h3>OFF</h3>");
  } else {
    client.print("<h3>ON</h3>");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button class=\"button\">ACCENDI </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button class=\"button\">SPEGNI </button></a><br />");  
  client.println("</html>");
 
    delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} // void loop()
