//Código base Smart Car Arduino
//Servo, Sensor, Bluetooth

// Alexandre Garcez Vieira
// tecagv@terra.com.br
// Skype: tecagv@live.com
// Licença: CC BY-NC-SA
// https://br.creativecommons.org/

#include <Servo.h>
Servo servo1;

int E1 = 10; //E1
int M1 = 12; //M1
int E2 = 11; //E2
int M2 = 13; //M2

int vel = 255; //Velocidade

int estado = 'c'; //Estado inicial (Parado)

int pecho = 2;  // Sensor Ultrassonico
int ptrig = 3;

int duracion, distancia;

int pisca[] = {4, 7, 8, 13}; // Pisca Alerta
int contador = 0;
int timer = 100; //1000 = 1 Segundo

void setup()  {

  Serial.begin(9600);
  pinMode(E2, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);

  pinMode(pecho, INPUT);
  pinMode(ptrig, OUTPUT);

  pinMode(13, OUTPUT); //Led do Sensor Ultrassonico
  pinMode(7, OUTPUT); //Pisca Farol
  pinMode(8, OUTPUT); //Pisca Farol
  pinMode(4, OUTPUT); //Buzina


  servo1.attach(11);
  servo1.write(101);

  {
    for (contador = 0; contador < 4; contador++) {
      pinMode(pisca[contador], OUTPUT);
    }
  }
}

void loop()  {

  if (Serial.available() > 0) {
    estado = Serial.read();
  }
  if (estado == 'a') {       //Frente
    analogWrite(M2, 0);
    analogWrite(M1, 0);
    analogWrite(E2, vel);
    analogWrite(E1, vel);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);

  }
  if (estado == 'b') {      //Esquerda
    analogWrite(M2, 0);
    analogWrite(M1, 0);
    analogWrite(E2, 0);
    analogWrite(E1, vel);
    //digitalWrite(50, LOW);
  }
  if (estado == 'c') {
    analogWrite(M2, 0);
    analogWrite(M1, 0);
    analogWrite(E2, 0);
    analogWrite(E1, 0);
    digitalWrite(7, LOW); //Pisca
    digitalWrite(8, LOW); //Pisca
    digitalWrite(4, LOW); //Buzina
    digitalWrite(13, LOW); //LED
    //digitalWrite(50, HIGH);
    //servo1.write(101);
  }
  if (estado == 'd') {      //Direita
    analogWrite(M2, 0);
    analogWrite(M1, 0);
    analogWrite(E1, 0);
    analogWrite(E2, vel);
    //digitalWrite(50, LOW);
  }

  if (estado == 'e') {      //Atrás
    analogWrite(E2, 0);
    analogWrite(E1, 0);
    analogWrite(M2, vel);
    analogWrite(M1, vel);
    //digitalWrite(50, LOW);
  }

  if (estado == 'f') {          //Auto

    digitalWrite(ptrig, HIGH);
    delay(0.01);
    digitalWrite(ptrig, LOW);

    duracion = pulseIn(pecho, HIGH);
    distancia = (duracion / 2) / 29;
    delay(10);

    if (distancia <= 30 && distancia >= 2) {
      digitalWrite(13, HIGH);

      analogWrite(M2, 0);
      analogWrite(M1, 0);
      analogWrite(E2, 0);
      analogWrite(E1, 0);
      delay (200);

      analogWrite(M2, vel);
      analogWrite(M1, vel);
      delay(500);

      analogWrite(M2, 0);
      analogWrite(M1, 0);
      analogWrite(E2, 0);
      analogWrite(E1, vel);
      delay(600);

      digitalWrite(13, LOW);
    }
    else {
      analogWrite(M2, 0);
      analogWrite(M1, 0);
      analogWrite(E2, vel);
      analogWrite(E1, vel);
    }
  }
  if (estado == 'g') {
    servo1.write(30);
    delay(1000);

    servo1.write(90);
    delay(700);

    servo1.write(150);
    delay(700);
  }
  if (estado == 'h') {
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(13, HIGH);
  }
  if (estado == 'm') {
    digitalWrite(13, 0);
  }
  if (estado == 'i') {
    digitalWrite(30, HIGH);
  }
  if (estado == 'n') {
    digitalWrite(M2, 0);
  }
  if (estado == 'z') {    
    digitalWrite(4, HIGH); // Buzina
  }
  if (estado == 'o') {
    digitalWrite(E2, 0);
  }
  if (estado == 'k') {
    digitalWrite(M1, 1);
  }
  if (estado == 'p') {
    digitalWrite(M1, 0);
  }
  if (estado == 'l') {
    digitalWrite(E1, 1);
  }
  if (estado == 'q') {
    for (contador = 0; contador < 4; contador++) {
      digitalWrite(pisca[contador], HIGH);
      delay(timer);
      digitalWrite(pisca[contador], LOW);
      delay(timer);
    }
  }
}
