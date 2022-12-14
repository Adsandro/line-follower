#include <hcsr04.h>

#define DireitoPositivo 12 // signal pin 1 for the right motor, connect to IN1               
#define DireitoNegativo 13  // signal pin 2 for the right motor, connect to IN2
#define ControleDireito 11 // enable pin for the right motor (PWM enabled)

#define EsquerdoPositivo 9 // signal pin 1 for the left motor, connect to IN3           
#define EsquerdoNegativo 8 // signal pin 2 for the left motor, connect to IN4
#define ControleEsquerdo 10 // enable pin for the left motor (PWM enabled)

#define SensorE 3 // Declara em qual porta estara saindo os dados dos sensores
#define SensorD 5

#define trigger 7
#define echo 6

#define led 2

bool sensorE = 0;
bool sensorD = 0;

int distancia = 66;

HCSR04 ultrassonico(trigger, echo);

int vAltaEsquerda = 100;
int vbaixaEsquerda = 0;

int vAltaDireita = 80;
int vBaixaDireita = 0;

int velocidade = 100; // Velocidade em condições perfeitas
int erro = 0;// Velocidade em caso o carrinho saia da rota
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

  pinMode(led, OUTPUT);

  delay(5000);
}

void loop(){

sensorE = digitalRead(SensorE);
sensorD = digitalRead(SensorD);
distancia = (ultrassonico.distanceInMillimeters());


Serial.println("");
Serial.print("Distancia:");
Serial.print(distancia);

Serial.println("");
Serial.print("Sensor Esquerdo:");
Serial.print(sensorE);

Serial.println("");
Serial.print("Sensor Meio:");

Serial.println("");
Serial.print("Sensor Direito:");
Serial.print(sensorD);


    if (distancia <= 100){
      motorA(parado);
      motorB(parado);
      luz(HIGH); 
    }  
    else if (sensorE == 1 and sensorD ==1) {
      motorA(vAltaEsquerda);
      motorB(vAltaDireita);     
      luz(LOW);
    }
    else if (sensorE == 1 and sensorD ==0) {
      motorA(vAltaEsquerda);
      motorBtras(erro);     
      luz(LOW);
    }
    else if (sensorE == 0 and sensorD ==1) {
      motorAtras(erro);
      motorB(vAltaDireita);     
      luz(LOW);
    }

    
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

void motorBtras(int veloc){
    digitalWrite(DireitoPositivo,HIGH);
    digitalWrite(DireitoNegativo,LOW);
    analogWrite(ControleDireito,veloc);
}

void motorAtras(int veloc){
    digitalWrite(EsquerdoPositivo,HIGH);
    digitalWrite(EsquerdoNegativo,LOW);
    analogWrite(ControleEsquerdo,veloc);
}

void luz(char valor){
    digitalWrite(led, valor);
}


