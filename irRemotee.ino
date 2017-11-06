#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo;//object of class servo
const int servo = A2;
int currpos, initpos, mappedvalue;
int RECV_PIN = A0;
IRrecv irrecv(RECV_PIN);
decode_results results;

int section;

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("Antenna:");
  irrecv.enableIRIn(); // Start the receiver
  myServo.attach(servo);
  if (irrecv.decode(&results))
    {
      initpos = 0xFFFF00;
      irrecv.resume();
    }
  lcd.setCursor(9,0);
  lcd.print(initpos);
  lcd.setCursor(0,1);
  lcd.print("Zone:");
}

void loop()
{
  if (irrecv.decode(&results))
    {
     currpos= results.value;
     irrecv.resume(); // Receive the next value
     if (initpos-currpos < 100){
      myServo.write(90);
      delay(15);
      section = 1;
     }
     if (initpos-currpos > 0){
      myServo.writeMicroseconds(180);
      delay(15);
      section = 2;
     }
      /*case 0xFF18E7:
      myServo.writeMicroseconds(1250);
      lcd.print("");
      delay(15);
      section = 2;
      break;
      case 0xFF7A85:
      myServo.writeMicroseconds(1500);
      delay(15);
      section = 3;
      break;
      case 0xFF10EF:
      myServo.writeMicroseconds(2000);
      delay(15);
      section = 4;
      break;
     }*/
     lcd.setCursor(9,1);
     lcd.print(section);
     
    }
}
