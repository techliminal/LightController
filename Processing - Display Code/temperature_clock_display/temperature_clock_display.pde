// Tempeature Clock by Malcolm Knapp. Serial code adapted from an example by Tom Igoe
// Version 02
// Serial port
import processing.serial.*;
Serial myPort;  // The serial port
String message = "";
String data = "";
String data1 = "";
String data2 = "";
int msgFlag = 0;
int index = 0;

//Display
float theta = 0;
float r;
float x;
float y;
float displayColor;
float displayLength;
float clockRate;

//Data storage
PrintWriter output;

int temptest = 80;
String prevMessage = "0.0"; 

void setup() {
  size(600, 600);
   background (0,0,0);
  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac

  myPort = new Serial(this, Serial.list()[0], 9600); // This looks at the first port in the Serial List
  output = createWriter("temperatue_history.txt");
  output.println ("Day,Hour,Second,Temperature");
}

void draw() {
  while (myPort.available() > 0) {
    int inByte = myPort.read();
    message = message + char(inByte);
    if (inByte == 37) {  // end of message check
    //  println(message);
      break;

    } 
  }
  if(message.equals("") == false){ // confirm there is a message
    if (message.substring(0,1).equals("?") && message.substring(message.length()-1, message.length()).equals("%")) { // well formed message check
       data = message.substring(1,message.length()-1);
       println(data);
       
       message = "";
       msgFlag = 0;
     }
    } else {
         data = ""; // bad message
      }
      
  if (msgFlag == 1) { // check for a message
    output.println ("" + day() + "," + hour() + "," + second() + "," + data); // records time stamp and temeperature
   
    displayColor = 10.0 + float(data)/10; // user defined
    displayLength = .50*float(data); //user defined 
    clockRate = 2.1; //user defined
    
    translate(width/2,height/2);
    smooth();
    colorMode (HSB, 100); 
    r = displayLength; 
    x = r*cos(theta);
    y = r*sin(theta);
    strokeWeight (3);
    stroke(displayColor,100,100);  
    line (0,0,x,y);
    theta += clockRate*PI/180f; //convert to radians. 
    data = "";
    msgFlag = 0;
  }
  delay(10);                                
}

void keyPressed() {
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  exit(); // Stops the program
}

