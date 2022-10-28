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
  if ((sensorE == 0) && (sensorD == 0)){
    digitalWrite(ControleEsquerdo, velocidade);
    digitalWrite(ControleDireito, velocidade);
  }

  if ((sensorE == 1) && (sensorD == 0)){
    digitalWrite(ControleEsquerdo, erro);
    digitalWrite(ControleDireito, velocidade);
  }  
  if ((sensorE == 0) && (sensorD == 1)){
    digitalWrite(ControleEsquerdo, velocidade);
    digitalWrite(ControleDireito, erro);
  }


if ((sensorE == 1) && (sensorD == 1)){
  //Definir esquema para dar meia volta
  }  
  
}
