#include <Arduino.h>
#include <WiFi.h>

String username = "";
String inputstr = "";
bool usernamecomplete = true;
bool stringComplete = false;
int commandMaxLen = 20;
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
  Serial.println("How do u want to be called");
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
	if(usernamecomplete){
    Serial.print("Hello ");
    Serial.println(cmd);
    Serial.println("What do u want from me?");
    usernamecomplete=false;
    stringComplete=false;
    commandMaxLen = 2;
   }

  else{
    sentf(inputstr);
  }
}

void sentf(String ara){
  while(!client.connected()){
    client.connect(servername, 80);
    delay(100);
  }
  client.print("GET /v1/x4.html?device=3&event=");
  client.print(ara[0]);
  client.print("&status=");
  client.println(ara[1]);
  client.stop();
  Serial.println("Already^_^");
}
