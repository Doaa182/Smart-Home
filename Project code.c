#include <LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd {12,11,7,8,9,10};

int temp = A0;

int motorPin=6 ;

int lightSensor =A1;

int led =5;

byte degree[8];

int servoPin1 = 3;
Servo myServo1;

int trig=1;
int echo=4;

int button1 = A2;
int button2 = A3;
int button3 = A4;

int Pattern[5]={1,3,1,2,2};

int userPattern [5];

int servoPin2 =2 ;
Servo myServo2;


bool correct;
bool first;
void setup()
{
  Serial.begin(9600);
  pinMode(temp, INPUT);
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  
  pinMode(motorPin,OUTPUT);
 

  
 
  
  pinMode(led, OUTPUT);
  
  pinMode(lightSensor, INPUT);
 
  myServo1.attach(servoPin1);
  myServo1.write(0); 
  
  lcd.createChar(1,degree);
  lcd.setCursor(12,0);
  lcd.write(1);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  


  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);

  myServo2.attach(servoPin2);
  myServo2.write(0);

}



void loop()
{
  
 
  if (correct==true){
  
    int value = analogRead(temp);
    float mv = value/1023.0;
    mv = mv*5;
    mv = mv-0.5;
    mv = mv*1000;
  float cl = mv/10;
  lcd.setCursor(0,0);
  lcd.print("Temp= ");
  lcd.print(cl);
  
byte degree[8]
{
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
 
    
    if (cl>=30)
  {
    digitalWrite(motorPin,HIGH);
  
    
  }
  else
  {
    digitalWrite(motorPin,LOW);
    
  }

  int light = analogRead(lightSensor);

  int mapValue= map(light,344,1017,0,255);
  analogWrite(led,mapValue);


  float duration,distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance = duration/29/2;
  
  
  if(distance<50)
  {
    myServo1.write(90);
  }
  else   
  {
    myServo1.write(0);
  }

  }
  
  else if (correct==false){
  
  int counter=0;
 while (counter<5){

  int valButton1 = digitalRead(button1);
  int valButton2 = digitalRead(button2);
  int valButton3 = digitalRead(button3);

    if (valButton1==1)
    {
     userPattern[counter] = 1;
      Serial.println(userPattern[counter]);
      counter++;
      delay(150);
		
    }


    else if (valButton2==1)
    {
      userPattern[counter] = 2;
      Serial.println(userPattern[counter]);
      counter++;
      delay(150);
		
    }

    else if (valButton3==1)
    {
      userPattern[counter] = 3;
      Serial.println(userPattern[counter]);
      counter++;
      delay(150);
		
    }
 

 int a=0;

   
  for (int i=0; i<=4;i++)
  {
    
   if( userPattern[i] == Pattern[i])
   {a++;}
  }

  
    if (a==5)
    {
     myServo2.write(90);
     lcd.setCursor(0,1);
     lcd.print("Correct Pattern");
      correct=true;
    }

    else if(a != 5 && first == true)
    {
      myServo2.write(0);
     lcd.setCursor(0,1);
     lcd.print("Wrong Pattern");
     correct=false;
    }
 	if (counter == 5)
      first = true;
   }
 
  }
  }
