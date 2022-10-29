#define DireitoPositivo 12 // signal pin 1 for the right motor, connect to IN1               
#define DireitoNegativo 13  // signal pin 2 for the right motor, connect to IN2
#define ControleDireito 11 // enable pin for the right motor (PWM enabled)

#define EsquerdoPositivo 9 // signal pin 1 for the left motor, connect to IN3           
#define EsquerdoNegativo 8 // signal pin 2 for the left motor, connect to IN4
#define ControleEsquerdo 10 // enable pin for the left motor (PWM enabled)

#define SensorE 7 // Declara em qual porta estara saindo os dados dos sensores
#define SensorD 6

bool sensorE = 0;
bool sensorD = 0;


int velocidade = 255; // Velocidade em condições perfeitas
int erro = 145; // Velocidade em caso o carrinho saia da rota

void setup() {
  
  Serial.begin(9600);
  
  pinMode(DireitoPositivo,OUTPUT);        
  pinMode(DireitoNegativo,OUTPUT);
  pinMode(ControleDireito,OUTPUT);
  
  pinMode(EsquerdoPositivo,OUTPUT);        
  pinMode(EsquerdoNegativo,OUTPUT);
  pinMode(ControleEsquerdo,OUTPUT);

  pinMode(sensorE, INPUT);
  pinMode(sensorD, INPUT);  


}

void loop(){

sensorE = digitalRead(SensorE);
sensorD = digitalRead(SensorD);
Serial.println("");
Serial.print("ValorE: ");
Serial.print(sensorE);
Serial.print("| ValorD: ");
Serial.print(sensorD);
  //Branco == 0, Preto == 1
  //Manter sensores na linha branca  
  //Frente
  if ((sensorE == 0) and (sensorD == 0)){
    motorA(velocidade);
    motorB(velocidade);
  }

  //Direita
  if ((sensorE == 1) and (sensorD == 0)){
    motorA(velocidade);
    motorB(erro);
  } 

  //Esquerda 
  if ((sensorE == 0) and (sensorD == 1)){
   motorA(erro);
   motorB(velocidade);   
  }

  // Ré
  if ((sensorE == 1) and (sensorD == 1)){
    motorB(0);
    motorA(0);
  }  
  
//motorA(velocidade);
//motorB(velocidade); 
  
}

//Motor Direita
void motorA(int veloc){
digitalWrite(DireitoPositivo,LOW);
digitalWrite(DireitoNegativo,HIGH);
analogWrite(ControleDireito,veloc);
}

//Motor Esquerda
void motorB(int veloc){
digitalWrite(EsquerdoPositivo,LOW);
digitalWrite(EsquerdoNegativo,HIGH);
analogWrite(ControleEsquerdo,veloc);
}

