#include <hcsr04.h>

#define DireitoPositivo 12 // signal pin 1 for the right motor, connect to IN1               
#define DireitoNegativo 13  // signal pin 2 for the right motor, connect to IN2
#define ControleDireito 11 // enable pin for the right motor (PWM enabled)

#define EsquerdoPositivo 9 // signal pin 1 for the left motor, connect to IN3           
#define EsquerdoNegativo 8 // signal pin 2 for the left motor, connect to IN4
#define ControleEsquerdo 10 // enable pin for the left motor (PWM enabled)

#define SensorE 3 // Declara em qual porta estara saindo os dados dos sensores
#define SensorD 5
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
  pinMode(sensorM, INPUT);

  pinMode(led, OUTPUT);

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
      Parado();
      luz(HIGH); 
    }  
    
else if ((sensorE == 1) and (sensorD == 1) and (sensorM == 0))  {
      Frente();
      luz(LOW);
  }

//SENSOR E e SENSOR M no preto e SENSOR D no branco, vira para esquerda até o M ficar no branco
else if ((sensorE == 1) and (sensorD == 0) and (sensorM == 1))  {
      Direita();
      luz(LOW);
  }

//SENSOR D e SENSOR M no preto e SENSOR E no branco, vira para direita até o M ficar no branco
else if ((sensorE == 0) and (sensorD == 1) and (sensorM == 1))  {
      Esquerda();
      luz(LOW); 
      }

}



void Frente(){
  digitalWrite(DireitoPositivo, LOW);
  digitalWrite(DireitoNegativo, HIGH);

  digitalWrite(EsquerdoPositivo, LOW);
  digitalWrite(EsquerdoNegativo, HIGH);

  analogWrite(ControleDireito, velocidade);
  analogWrite(ControleEsquerdo, velocidade);
  delay(4);
}


void Esquerda(){
  digitalWrite(DireitoPositivo, LOW);
  digitalWrite(DireitoNegativo, HIGH);

  digitalWrite(EsquerdoPositivo, LOW);
  digitalWrite(EsquerdoNegativo, LOW);

  analogWrite(ControleDireito, velocidade);
  analogWrite(ControleEsquerdo, erro);
  delay(4);
}

void Direita(){
  digitalWrite(DireitoPositivo, LOW);
  digitalWrite(DireitoNegativo, LOW);

  digitalWrite(EsquerdoPositivo, LOW);
  digitalWrite(EsquerdoNegativo, HIGH);

  analogWrite(ControleDireito, erro);
  analogWrite(ControleEsquerdo, velocidade);
  delay(4);
}

void Parado(){
  digitalWrite(DireitoPositivo, LOW);
  digitalWrite(DireitoNegativo, LOW);

  digitalWrite(EsquerdoPositivo, LOW);
  digitalWrite(EsquerdoNegativo, LOW);

  analogWrite(ControleDireito, 0);
  analogWrite(ControleEsquerdo, 0);
  delay(4);

}

void luz(char valor){
    digitalWrite(led, valor);
}


