
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 8; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 6;
int numberOfVerticalDisplays = 2;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
String rute;
String tiempo;
String tape ;
int wait = 50; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

void setup() {
  Serial.begin(9600);
  matrix.setIntensity(5); // Use a value between 0 and 15 for brightness

  // Adjust to your own needs
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 1, 0); // The second display is at <1, 0>
  matrix.setPosition(2, 2, 0); // The third display is at <2, 0>
  matrix.setPosition(3, 3, 0); // And the last display is at <3, 0>
  matrix.setPosition(4, 4, 0); // The first display is at <0, 0>
  matrix.setPosition(5, 5, 0); // The second display is at <1, 0>
  matrix.setPosition(6, 5, 1); // The third display is at <2, 0>
  matrix.setPosition(7, 4, 1); // And the last display is at <3, 0>
  matrix.setPosition(8, 3, 1); // The first display is at <0, 0>
  matrix.setPosition(9, 2, 1); // The second display is at <1, 0>
  matrix.setPosition(10, 1, 1); // The third display is at <2, 0>
  matrix.setPosition(11, 0, 1); // And the last display is at <3, 0>
  //  ...
  matrix.setRotation(0, 1);    // The first display is position upside down
  matrix.setRotation(1, 1);    // The same hold for the last display
  matrix.setRotation(2, 1);    // The first display is position upside down
  matrix.setRotation(3, 1);    // The same hold for the last display
  matrix.setRotation(4, 1);    // The first display is position upside down
  matrix.setRotation(5, 1);    // The same hold for the last display
  matrix.setRotation(11, 3);    // The first display is position upside down
  matrix.setRotation(10, 3);    // The same hold for the last display
  matrix.setRotation(9, 3);    // The same hold for the last display
  matrix.setRotation(8, 3);    // The same hold for the last display
  matrix.setRotation(7, 3);    // The same hold for the last display
  matrix.setRotation(6, 3);    // The same hold for the last 
    matrix.fillScreen(LOW);
}

void loop() {
//while(Serial.available() > 0)
  //{
    //tape = Serial.readString();
    //tape = Serial.readStringUntil('\n');
    rute = Serial.readStringUntil(',');
    tiempo = Serial.readStringUntil(',');
    tape = Serial.readStringUntil('\n');
    while(Serial.available() < 1)
      {
            matrix.drawChar(4,1,':', HIGH, LOW, 1);
            matrix.drawChar(0,1,'R', HIGH, LOW, 1);
            matrix.drawChar(32,1,':', HIGH, LOW, 1);
            matrix.drawChar(28,1,'T', HIGH, LOW, 1);
            matrix.write();
        printstate();
      }
      Serial.print(rute);
      Serial.print(",");
      Serial.print(tiempo);
      
}

void printstate(){
    
    //matrix.drawPixel(0,0,1);matrix.drawPixel(1,0,1);matrix.drawPixel(2,0,1);matrix.drawPixel(3,0,1);matrix.drawPixel(4,0,1);
    //matrix.drawPixel(1,1,1);matrix.drawPixel(2,1,1);matrix.drawPixel(3,1,1);matrix.drawPixel(2,2,1);matrix.drawPixel(2,3,1);matrix.drawPixel(2,4,1);matrix.drawPixel(2,5,1);//antena
    //matrix.drawChar(0, 11,"M:", HIGH, LOW, 1);
    matrix.drawChar(8, 1, rute[0], HIGH, LOW, 1);
    matrix.drawChar(14, 1, rute[1], HIGH, LOW, 1);
    matrix.drawChar(37,1,tiempo[0], HIGH, LOW, 1);
    matrix.drawChar(43,1,tiempo[1], HIGH, LOW, 1);
    matrix.write(); // Send bitmap to display
    delay(10000);
    for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = 8; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write(); // Send bitmap to display

    delay(wait);
  }
  
}
