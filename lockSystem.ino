//including library for basic functions
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;
int pos=0; 
// pins for LCD
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
const byte rows=4;
const byte cols=3;
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={1,2,3,4};
byte colPins[cols]={5,6,7};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="4567";
int currentposition=0;

void setup()
{
 
displayscreen();
Serial.begin(9600);
myservo.attach(9); //attaching servo to pin number 9//
 
lcd.begin(16,2);
 
}
 
void loop()
{
if( currentposition==0)
{
displayscreen();
 
}
int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{
 
lcd.print("*");
keypress();
}
 
if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{
 
servoRotate();
currentposition=0;
 
}
 
}
 
else
{
++invalidcount;
incorrect();
currentposition=0;
 
}
 
}
}

 
//door open function//
void servoRotate()
{
delay(900);
lcd.setCursor(1,0);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");
 
for(pos = 180; pos>=0; pos-=5) // servo goes from 180 degrees to 0 degrees (opening the door)
{
myservo.write(pos); // tells servo to go to position in variable 'pos'
delay(5);
}
delay(2000);
 
 
 
delay(1000);
countDown();
 
delay(1000);
for(pos = 0; pos <= 180; pos +=5) // goes from 0 degrees to 180 degrees
{
myservo.write(pos); // tells servo to go to position in variable 'pos'
delay(15);
currentposition=0;
lcd.clear();
displayscreen();
 
}
}
 
//when there is wrong password//
void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("incorrect pass!try again");
 
lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("CODE INCORRECT");
delay(3000);
lcd.clear();
displayscreen();
}


//**This clears the screen**//
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}


//**DISPALAY FUNCTION**//
void displayscreen()
{
lcd.setCursor(0,0);
lcd.println("*ENTER THE CODE*");
lcd.setCursor(1 ,1);
lcd.println("TO _/_ (OPEN)!!");
}

//**ARM SERVO**//
void armservo()
{
for (pos=180;pos<=180;pos+=50)
{
myservo.write(pos);
delay(5);
}
delay(5000);
 
for(pos=180;pos>=0;pos-=50)
{
myservo.write(pos);
}
 
}
 
//**count down**//
void countDown()
{
delay(1200);
lcd.clear();
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(200);
lcd.println("GET IN WITHIN:::");
 
lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);


lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);


lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //3
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);


lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //4
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);


lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");
delay(1000);


lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED!");
delay(440);
}
