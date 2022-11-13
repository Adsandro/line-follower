#include <hcsr04.h>

#define DireitoPositivo 12 // signal pin 1 for the right motor, connect to IN1               
#define DireitoNegativo 13  // signal pin 2 for the right motor, connect to IN2
#define ControleDireito 11 // enable pin for the right motor (PWM enabled)

#define EsquerdoPositivo 9 // signal pin 1 for the left motor, connect to IN3           
#define EsquerdoNegativo 8 // signal pin 2 for the left motor, connect to IN4
#define ControleEsquerdo 10 // enable pin for the left motor (PWM enabled)

#define SensorE 5 // Declara em qual porta estara saindo os dados dos sensores
#define SensorD 3
#define SensorM 4

#define trigger 7
#define echo 6

#define led 2

bool sensorE = 0;
bool sensorD = 0;
bool sensorM = 0;

int distancia = 66;

HCSR04 ultrassonico(trigger, echo);


int velocidade = 150; // Velocidade em condições perfeitas
int erro = 90; // Velocidade em caso o carrinho saia da rota
int parado = 0;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(DireitoPositivo, OUTPUT);        
  pinMode(DireitoNegativo, OUTPUT);
  pinMode(ControleDireito, OUTPUT);
  
  pinMode(EsquerdoPositivo, OUTPUT);        
  pinMode(EsquerdoNegativo, OUTPUT);
  pinMode(ControleEsquerdo, OUTPUT);

  pinMode(sensorE, INPUT);
  pinMode(sensorD, INPUT);  
  pinMode(sensorM, INPUT);

  pinMode(led, INPUT);

  delay(5000);
}

void loop(){

sensorE = digitalRead(SensorE);
sensorD = digitalRead(SensorD);
sensorM = digitalRead(SensorM);
distancia = (ultrassonico.distanceInMillimeters());


Serial.println("");
Serial.print("Distancia:");
Serial.print(distancia);

Serial.println("");
Serial.print("Sensor Esquerdo:");
Serial.print(sensorE);

Serial.println("");
Serial.print("Sensor Meio:");
Serial.print(sensorM);

Serial.println("");
Serial.print("Sensor Direito:");
Serial.print(sensorD);


    if (distancia <= 100){
      motorA(parado);
      motorB(parado);
    } 
    else if ((sensorE == 0) and (sensorD == 0) and (sensorM == 0))  {
      motorA(velocidade);
      motorB(velocidade);
  }
    else if ((sensorE == 0) and (sensorD == 1) and (sensorM == 0))  {
      motorA(velocidade);
      motorB(velocidade);
  }
    else if ((sensorE == 1) and (sensorD == 0) and (sensorM == 0))  {
      motorA(velocidade);
      motorB(velocidade);
  }
   else if ((sensorE == 1) and (sensorD == 0) and (sensorM == 1)) {
      motorA(erro);
      motorB(velocidade);
  } 
   else if ((sensorE == 0) and (sensorD == 1) and (sensorM == 1)){
      motorA(velocidade);
      motorB(erro);   
  }

  delay(0);
  
}

void motorB(int veloc){
digitalWrite(DireitoPositivo,LOW);
digitalWrite(DireitoNegativo,HIGH);
analogWrite(ControleDireito,veloc);
}

void motorA(int veloc){
digitalWrite(EsquerdoPositivo,LOW);
digitalWrite(EsquerdoNegativo,HIGH);
analogWrite(ControleEsquerdo,veloc);
}


