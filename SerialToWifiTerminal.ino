/*
 *  Connect to OBLink MX and send some commands!
 *     Created by Wade Oler
 */
 
 #include <ESP8266WiFi.h>
int debug = 0;

const char* ssid     = "Boringname";//"boring name";  //What is my ssid
const char* password = "letmeinhere";//"letmeinhere";  //ssid password

const char* host = "10.10.10.01";
int response = 0;
int Command = 0;
int NumOfCommands = 4;


const char* ListOfCommands[] = {"ATL1",
                                "ATH1",
                                "ATS1",
                                "ATAL",
                                //"ATIGN",
                                "ATMA"};
WiFiClient client;
//WiFiUDP Puke;
void setup()
{
  WiFi.begin(ssid, password);
  Serial.begin(115200);    //setup for terminal debug

  delay(500);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  if(debug != 1){
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }
  
  Serial.println("\nIP address: ");
  Serial.println(WiFi.localIP());
  if(debug != 1){
    if (client.connect(host, 35000)) {
      Serial.println("connected");
    }
  }
}


void loop()
{
  //look for a response from Car 
  if (client.available()) {
    String c = client.readString();
    Serial.print(c);
//    if(c.indexOf('>')>0){
//      response = 0; //reset gating flag
//      Serial.flush();
//    }
  }
  
  if(debug != 1){
    //Send a list of preprogrammed commands before 
    //terminal input for additional commands
    //Gate sending a command until you recieve a response
    if ((client.connected())&&(response ==0)) {
      response =1; //Flag that a command was sent
      if(Command < NumOfCommands){
        client.println(String(ListOfCommands[Command]));
        Serial.println(Command);
        Command++;
      }
    }
  }
  
  //look for command from Terminal
  if(Serial.available() > 0){
    char stuff = Serial.read();
    //Serial.print(stuff);
    client.println(String(stuff));
  }
}
