#include <Arduino.h>
#include <WiFi.h>

String username;
String inputstr;
String outputstr;
bool stringComplete=false;
int commandMaxLen=20;
int status=WL_IDLE_STATUS;
char ssid[]="urssid";
char password[]="urpassword";
char servername[]="p4.zmail.in.net";
void serialEvent();
void cmdProc(String);
void sentf(String);
WiFiClient client;

void setup(){
	Serial.begin(9600);
  while (status != WL_CONNECTED){
  	status=WiFi.begin(ssid, password);
    delay(1000);
	  }
  Serial.println("It's workin'");
  Serial.println("Only for u <3");
  }

void loop(){
	if (Serial.available()){
  	serialEvent();
	  }
	if (stringComplete){
  	cmdProc(inputstr);
  	inputstr = "";
  	stringComplete = false;
	  }
  }

void serialEvent(){
	while (Serial.available()){
 		char inChar = (char)Serial.read();
 		Serial.print(inChar);
 		if (inChar == '\n'){
 			stringComplete = true;
 		  }
    else{
 			if (inputstr.length() < commandMaxLen){
 				inputstr += inChar;
 			  }
      else{
      	stringComplete = true;
      	}
		 	}
	  }
  }

void cmdProc(String cmd){
	cmd.trim();
	if(cmd.startsWith("sent")){
		sentf(cmd);
	  }
	else if(cmd.startsWith("disconnect")){
		WiFi.disconnect();
		Serial.println("Disconnected");
	  }
  }

void sentf(String ara){
	client.stop();
  while(!client.connected()){
    client.connect(servername, 80);
		delay(100);
		Serial.println("connecting to site");
    }
  client.print("GET /v1/x4.html?device=3&event=");
  client.print(ara[5]);
	Serial.println(ara[5]);
  client.print("&status=");
  client.println(ara[7]);
	Serial.println(ara[7]);
	}
