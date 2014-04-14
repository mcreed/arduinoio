#include <SocketIOClient.h>
#include <Ethernet.h>
#include <SPI.h>

SocketIOClient client;

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x35, 0x1C };
char hostname[] = "166.78.63.23";
int port = 8080;
int led = 13;

// websocket message handler: do something with command from server
void ondata(SocketIOClient client, char *data) {

    digitalWrite(led, HIGH);   // turn the LED on
    Serial.print(data);        // print incoming data
    delay(1000);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off

}

void setup() {

  	Serial.begin(9600);
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH);

	Ethernet.begin(mac);
    Serial.println(Ethernet.localIP()); // printout IP address for debug purposes
    delay(1000);

	client.setDataArrivedDelegate(ondata);
	if (!client.connect(hostname, port)) Serial.println(F("Not connected."));
	if (client.connected()) client.send("Arduino 4 here!");
    digitalWrite(led, LOW);

}

void loop() {
	client.monitor();
}
