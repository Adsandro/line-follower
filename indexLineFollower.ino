const int motorRPin1 = 12; // signal pin 1 for the right motor, connect to IN1               
const int motorRPin2 = 13;  // signal pin 2 for the right motor, connect to IN2
const int motorREnable = 11; // enable pin for the right motor (PWM enabled)

const int motorLPin1 = 9; // signal pin 1 for the left motor, connect to IN3           
const int motorLPin2 = 8; // signal pin 2 for the left motor, connect to IN4
const int motorLEnable = 10; // enable pin for the left motor (PWM enabled)

const int sensor1 = 7; // Declara em qual porta estara saindo os dados dos sensores
const int sensor2 = 6;
const int sensor3 = 5;
const int sensor4 = 4;

int motorSpeed = 255; // Velocidade em condições perfeitas
int error = 145; // Velocidade em caso o carrinho saia da rota

void setup() {
  
  Serial.begin(9600);
  
  
  pinMode(motorLPin1,OUTPUT);        
  pinMode(motorLPin2,OUTPUT);
  pinMode(motorLEnable,OUTPUT);
  
  pinMode(motorRPin1,OUTPUT);        
  pinMode(motorRPin2,OUTPUT);
  pinMode(motorREnable,OUTPUT);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
   

}

void loop(){
  
}

void scanD() {

}
