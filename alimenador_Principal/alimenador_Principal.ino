#include <Servo.h>
#include<Wire.h>
#include<RTClib.h>

RTC_DS1307 RTC; // objeto rtc relogio 
Servo myservo; // def o objeto servo se referindo ao servo motor

int fechado;
int angulo;   //inteiro para declarar posiçao
int repeticao;
int tempo;

void setup() 	{
  
Serial.begin(57600);
Wire.begin();
RTC.begin();

if (! RTC.isrunning())  { 
   Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
   // RTC.adjust(DateTime(__DATE__, __TIME__));
  			}

myservo.attach(9); // define que pin o servo esta conectado 
  
		}
void loop() {

angulo = 60;
repeticao = 10;
tempo = 1200;
fechado = 80;
myservo.write(fechado);

DateTime now = RTC.now();
Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
 
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now.unixtime() + 7 * 86400L + 30);

    Serial.println();
    delay(1000);



if (now.hour() == 17 && now.minute() == 28 && now.second() == 30){

//time goes up here
repetidordeFuncao(tempo,repeticao,angulo,fechado);
								 }

                 
if (now.hour() == 15 && now.minute() == 28 && now.second() == 30){

//time goes up here
repetidordeFuncao(tempo,repeticao,angulo,fechado);
                }

                
if (now.hour() == 12 && now.minute() == 28 && now.second() == 30){

//time goes up here
repetidordeFuncao(tempo,repeticao,angulo,fechado);
                 }


                 
if (now.hour() == 8 && now.minute() == 28 && now.second() == 30){

//time goes up here
repetidordeFuncao(tempo,repeticao,angulo,fechado);
                }


	    }

void repetidordeFuncao(int segundos,int repeticao,int angulo, int fechando){//later use pointers to call the function
//funcao abre e fecha abertura do cano segundos se refere ao tempo aberto em mili secs , repeticao se refere ao numero de vezes 
//para abrir e fechar a abertura angulo se refere ao angulo de abertura.
int i = 0;
for(i;i<repeticao;i++)	{
AbrindoeFechando(segundos,angulo,fechado);
			}
						}

void AbrindoeFechando(int segundos,int angulo,int fechado){
myservo.write(angulo);
delay(segundos);
myservo.write(fechado); //fecha //closes
delay(segundos);
				}
