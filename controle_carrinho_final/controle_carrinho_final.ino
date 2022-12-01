#include "hcsr04.h" //Biblioteca do Sensor Ultrassônico

#define SENSOR_ESQ 3 // Sensor IR esquerdo definido no pin 6 do arduino
#define SENSOR_MEIO 4 // Sensor IR médio definido no pin 5 do arduino
#define SENSOR_DIR 5 // Sensor IR direito definido no pin 4 do arduino

#define led 2 // Pin para uma led

//Pinos definidos para controlar os motores, esses são conectados as entradas IN1, IN2, IN3, IN4, ENA e ENB da Ponte-H
#define dirFrente 12
#define dirTras 13
#define esqFrente 9
#define esqTras 8
#define ENA 10
#define ENB 11

// Variáveis para controlar os estados dos Sensores IR a fim de identificar presença ou ausência de cor
int estadoEsq = 0;
int estadoMeio = 0;
int estadoDir = 0;

unsigned long millisParada = millis();

HCSR04 ultraS(7, 6); //Objeto do sensor ultrassônico

//Classe Motor e seus métodos.
class Motor {
  
  int pin1, pin2, EN, pinEN; //Pinos de cada motor
  
  public:
    //Método para declaração dos pinos dos motores dentro do void setup()
    void saidaPino(int in1, int in2, int EN){  
      pin1 = in1;
      pin2 = in2;
      pinEN = EN;
      pinMode(pin1, OUTPUT);  
      pinMode(pin2, OUTPUT);
      pinMode(pinEN, OUTPUT);
    }

    //Método para redefinir velocidade desse motor
    void defineVelocidade(int valor){
      analogWrite(pinEN, valor);
    }

    //Método para girar o motor no sentido padrão.
    void frente(){
      digitalWrite(pin1, HIGH); 
      digitalWrite(pin2, LOW) ;
    }

    //Basicamente um método inverso do frente(), invertendo o tipo de sáida nos pinos que recebem voltagem.
    void tras(){
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
    }

    //Quando os dois pinos estão recebendo uma voltagem alta (HIGH) o motor trava, esse é o modo de parada recomendado para o motor.
    void para(){
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
    }

};

Motor motor1, motor2; // Criação de dois objetos do tipo Motor

//Função que chama os métodos de ambos motores para ir para direita.
void direita(void) {
   motor1.defineVelocidade(150);
   motor2.defineVelocidade(50);
   motor1.frente();
   motor2.frente();
}

//Função que chama os métodos de ambos motores para ir para esquerda.
void esquerda(void) {
  motor2.defineVelocidade(150);
  motor1.defineVelocidade(50);
  motor1.frente();
  motor2.frente();
}

//Função que chama os métodos de ambos motores para seguir em frente.
void frente(void) {
  motor1.defineVelocidade(170);
  motor2.defineVelocidade(150);
  motor1.frente();
  motor2.frente();
}

//Função que chama os métodos de ambos motores para ir para trás.
void tras(void) {
  motor1.defineVelocidade(150);
  motor2.defineVelocidade(150);
  motor1.tras();
  motor2.tras();
}

//Função que para tudo.
void para(void) {
  motor1.defineVelocidade(0);
  motor2.defineVelocidade(0);
  motor2.para();
  motor1.para();
}


//Função que lê os sensores infravermelhos e usa a estrutura de decisão "if" para automatizar o carrinho
void estadoSensor(void) {
  if(ultraS.distanceInMillimeters() <= 100){
    digitalWrite(led, HIGH);
    para();
  }else{
    estadoEsq = digitalRead(SENSOR_ESQ);
    estadoDir = digitalRead(SENSOR_DIR);
    estadoMeio = digitalRead(SENSOR_MEIO);
  
    if(estadoEsq == 0 and estadoDir == 0 and estadoMeio == 0){
      frente();
      digitalWrite(led, LOW);
    }
    else if(estadoEsq == 0 and estadoDir == 0 and estadoMeio == 1){
      frente();
      digitalWrite(led, LOW);
    }
    else if(estadoEsq == 0 and estadoDir == 1 and estadoMeio == 0){
      frente();  
      digitalWrite(led, LOW);
    }
    else if(estadoEsq == 0 and estadoDir == 1 and estadoMeio == 1){
      direita();
      digitalWrite(led, LOW);
    }
    else if(estadoEsq == 1 and estadoDir == 0 and estadoMeio == 0){
      frente();
      digitalWrite(led, LOW);
    }
    else if(estadoEsq == 1 and estadoDir == 0 and estadoMeio == 1){
      frente();
      digitalWrite(led, LOW);
    }
    else if(estadoEsq == 1 and estadoDir == 1 and estadoMeio == 0){
      esquerda();
      digitalWrite(led, LOW);
    }
    else if(estadoEsq == 1 and estadoDir == 1 and estadoMeio == 1){
      tras();
      digitalWrite(led, LOW);
    }
  }
}

//A função built-in setup é chamada uma única vez quando o arduino liga.
void setup() {
  pinMode(led, OUTPUT);

  //Incialização de todos os pinos importantes.
  motor1.saidaPino(dirFrente, dirTras, ENB); 
  motor2.saidaPino(esqFrente, esqTras, ENA);
  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_DIR, INPUT);
  pinMode(SENSOR_MEIO, INPUT);

  delay(5000);
}

// Principal função, é chamada constantemente
void loop() {
  if(millis() - millisParada > 10000){
    para();
  }else{
    estadoSensor();
  } 
}
