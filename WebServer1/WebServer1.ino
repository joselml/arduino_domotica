/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,0,177);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

int fr=A0;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // inicializar puertos
  pinMode(8,OUTPUT);
  // pinMode(fr,INPUT);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = false;
    boolean get=true,gs=false;
    String Mg;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // Serial.write(c);
        if (get){
          if (c=='H'){
            get=false;
          }
          else if(c=='?' || gs){
            gs=true;
            if (c!='/')Mg+=c;
          }
        }
        //  Serial.println("mg: "+Mg)
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          if (SearchGet(Mg,"index")!="None"){
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            // add a meta refresh tag, so the browser pulls again every 5 seconds:
            //  client.println("<meta http-equiv=\"refresh\" content=\"5\">");
            // output the value of each analog input pin
            client.println("Hola Mundo! Desde Arduino!:D");
            client.println("<input type=button value='Encender led' onclick=\"location.href='http://192.168.0.177?led=6&estado=1&index';\"/><input type=button value='Apagar led' onclick=\"location.href='http://192.168.0.177?led=6&estado=0&index';\"/>");
            client.println("<input type=button value='Encender led' onclick=\"location.href='http://192.168.0.177?led=7&estado=1&index';\"/><input type=button value='Apagar led' onclick=\"location.href='http://192.168.0.177?led=7&estado=0&index';\"/>");

            //  client.println(Mg);
            // client.println(SearchGet(Mg,"led"));
            //  client.println(analogRead(fr));
            //    client.println("<input type=button value='Foto resitencia' onclick='fr()'><div id=\"fr\"></div><script type=\"text/javascript\">var server=\"http://192.168.0.177?\",state_complete=4,peticion = null;function xhr(){ if(window.XMLHttpRequest) {    return new XMLHttpRequest();  }  else if(window.ActiveXObject) {     return new ActiveXObject(\"Microsoft.XMLHTTP\");  }}function valida(url,fun,method,data){peticion=xhr();peticion.onreadystatechange=fun;peticion.open(\"GET\",url,true);peticion.setRequestHeader(\"Content-Type\", \"application/text\");peticion.send(null);}function fr(){valida(server+\"fr=1\",function(){if (peticion.readyState==state_complete){    if(peticion.status == 200 ) {            document.getElementById(\"fr\").innerHTML=peticion.response;            console.log(peticion);          }}},\"GET\")}</script>");
            client.println("</html>");
          }
          break;

        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
    String led=SearchGet(Mg,"led");
    String estado=SearchGet(Mg,"estado");
    
    if (estado=="1"){
      digitalWrite(led.toInt() ,HIGH);
    }
    if (estado=="0"){
      digitalWrite(led.toInt(),LOW);    
    }

  }


}





String SearchGet(String get,String search){
  int pos=get.indexOf(search);
  boolean continuar=false;
  if (pos!=-1){
    String str="";
    for (int i; i<get.length();i++){
      if (get[pos]!='&'){
        if (get[pos]=='=' || continuar){
          if(get[pos]!='=')str+=get[pos];
          continuar=true;
        }
        pos++;
      }
      else{
        break;
      }
    }
    str.replace(" ","");
    //Serial.println(str);

    return str;
  }
  else{
    return "None";
  }
}






