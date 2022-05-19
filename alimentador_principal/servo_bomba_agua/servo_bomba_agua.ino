#include "Servo.h"
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>

/**
 *@file servo_bomba_agua.ino
 *
 *@mainpage Servo_food_water Doc
 *
 *@section libraries Libraries
 *
 *Servo-version:1.1.7 by Arduino\n
 *RTClib-version:2.0.2 by Adafruit\n
 *Keypad-version:3.1.1 by Community,github/Chris-A/Keypad\n
 *
 *@section author Author
 *- Created by Mr-76
 */

RTC_DS1307 RTC; //RTC object 
Servo myservo; //servo object
int PINO_RELE = D5;

void setup(){
	Serial.begin(57600);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PINO_RELE,OUTPUT);
		
	
	if (! RTC.begin()) {
		Serial.println("Couldn't find RTC");
		Serial.flush();
		// while (1) delay(10);
	}

	if (! RTC.isrunning()) {
		Serial.println("RTC is NOT running, let's set the time!");
		//RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
		RTC.adjust(DateTime(2022, 5, 17, 17, 11, 0));
	}
  //RTC.adjust(DateTime(2022, 5, 17, 17, 11, 0));
  
	myservo.attach(D4);
	myservo.write(155);
  
}


void loop() {
	DateTime now = RTC.now();
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.println();
	delay(1000);
	//servo_tester(120,90,myservo);
	ativado(5,12,17,30,now,myservo);
	watering_plants(6,30,2,now);

}

/**
*Tests if the servo motor is working
*@param open_angle
*angle to open the exit of food
*@param close_angle
*angle to close the exit of food
*@param my_servo
*Servo object to run the commands
*@return
*void
*/

void servo_tester(int open_angle,int close_angle,Servo my_servo){
	Serial.println("Opening");
	//delay(2000);
	my_servo.write(open_angle);
	delay(2000);
	Serial.println("Closing...");
	//delay(2000);
	my_servo.write(close_angle);
	delay(2000);
}

/**
*water pump activation function
*@param hour
*hour to activate the pump
*@param minute
*minute to activate the pump
*@param tempo_aguar
*time of the pump on
*@param DateTime
*Receives a date time object
@return void
*/
void watering_plants(int hour,int minute,int tempo_aguar,DateTime now){
	if (now.hour() == hour && now.minute() == minute){
		digitalWrite(PINO_RELE,HIGH);
		delay(tempo_aguar*60000);
		digitalWrite(PINO_RELE,LOW);
  	}
}

/**
*activates the servo based on 
*4 timings
*@param hour1
*first hour timing
*@param hour2
*second hour timing
*@param hour3
*third hour timing
*@param minutes
*minuts timing
*@param DateTime
*receives a date time object
@return void
*/
void ativado(int hour1,int hour2,int hour3,int minutes1,DateTime now,Servo my_servo){
	Serial.println("function ativado");
	int angle  = 180;
	int repeat = 2;
	int timing = 1700;
	int closed = 155;
	int timings_array[] = {hour1,hour2,hour3};
	int size_array = (sizeof(timings_array)/sizeof(int));//tamanho do array para loop
	for(int i = 0;i < size_array;i++){
		if ((now.hour()) == (timings_array[i])){
			Serial.println("function ativado inside 1");
			if ((now.minute()) == (minutes1)){
				Serial.println("function ativado inside 2");
				for(int repeat_times = 0; repeat_times < repeat; repeat_times++){
					Serial.println("repeater func1");
					activate_servo(angle,closed,myservo,timing); 
					delay(1000);
				}
				delay(60000);//pass 1 min
			}else{
				break;
			}
		}else{
			continue;
		}
	}
}

/**
*Activates the servo
*@param open_angle
*angle to open the exit of food
*@param close_angle
*angle to close the exit of food
*@param my_servo
*Servo object to run the commands
*@return
*void
*/
void activate_servo(int open_angle,int close_angle,Servo my_servo,int timing){

	Serial.println("Opening");
	my_servo.write(open_angle);
	delay(timing);
	Serial.println("Closing...");
	my_servo.write(close_angle);
	delay(timing);
}
