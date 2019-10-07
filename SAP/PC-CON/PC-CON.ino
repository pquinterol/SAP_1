//Bibliotecas
#include<TimerOne.h>

//Outputs
#define LM 31
#define CE 32
#define EE 33
#define LI 34
#define EI 35
#define LA 36
#define EA 37
#define EU 38
#define LB 39
#define LO 40

#define ADD 18
#define SUB 19
#define MUL 20
#define DIV 21
#define ECON 50

#define ERRPIN 2

//Clock
#define CLK 53

bool clkState = false;
const int D_TIME = 100;
unsigned int PC;
bool did_goto = false;
unsigned int saved_PC;

//PORTA nos va a permitir leer las instrucciones
//PORTL nos va a permitir transmitir el numero de linea del programa al BUS

void lda() {
  digitalWrite(EI, HIGH);
  digitalWrite(LM, HIGH);
  rSignal();
  digitalWrite(LM, LOW);
  digitalWrite(EI, LOW);
  digitalWrite(CE, HIGH);
  digitalWrite(EE, HIGH);
  digitalWrite(LA, HIGH);
  rSignal();
  digitalWrite(LA, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(EE, LOW);
  //PC++;
  Serial.println("LDA Finish");

}

void add() {
  //Poner en el puerto el numero de la direccion de LDB
  digitalWrite(EI, HIGH);
  digitalWrite(LM, HIGH);
  rSignal();
  digitalWrite(LM, LOW);
  digitalWrite(EI, LOW);
  digitalWrite(CE, HIGH);
  digitalWrite(EE, HIGH);
  digitalWrite(LB, HIGH);
  rSignal();
  digitalWrite(LB, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(EE, LOW);
  digitalWrite(ADD, HIGH);
  digitalWrite(ADD, LOW);
  digitalWrite(EU, HIGH);
  digitalWrite(LA, HIGH);
  rSignal();
  digitalWrite(LA, LOW);
  digitalWrite(EU, LOW);
  //PC++;
}

void sub() {
  digitalWrite(EI, HIGH);
  digitalWrite(LM, HIGH);
  rSignal();
  digitalWrite(LM, LOW);
  digitalWrite(EI, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(EE, HIGH);
  rSignal();
  digitalWrite(LB, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(EE, LOW);
  digitalWrite(SUB, HIGH);
  digitalWrite(SUB, LOW);
  digitalWrite(EU, HIGH);
  digitalWrite(LA, HIGH);
  rSignal();
  digitalWrite(LA, LOW);
  digitalWrite(EU, LOW);
  //PC++;

}

void divi() {
  digitalWrite(EI, HIGH);
  digitalWrite(LM, HIGH);
  rSignal();
  digitalWrite(LM, LOW);
  digitalWrite(EI, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(EE, HIGH);
  rSignal();
  digitalWrite(LB, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(EE, LOW);
  digitalWrite(DIV, HIGH);
  digitalWrite(DIV, LOW);
  digitalWrite(EU, HIGH);
  digitalWrite(LA, HIGH);
  rSignal();
  digitalWrite(LA, LOW);
  digitalWrite(EU, LOW);
  //PC++;
}

void mul() {
  digitalWrite(EI, HIGH);
  digitalWrite(LM, HIGH);
  rSignal();
  digitalWrite(LM, LOW);
  digitalWrite(EI, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(EE, HIGH);
  rSignal();
  digitalWrite(LB, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(EE, LOW);
  digitalWrite(MUL, HIGH);
  digitalWrite(MUL, LOW);
  digitalWrite(EU, HIGH);
  digitalWrite(LA, HIGH);
  rSignal();
  digitalWrite(LA, LOW);
  digitalWrite(EU, LOW);
  //PC++;
}

void pw2() {
  digitalWrite(EA, HIGH);
  digitalWrite(LB, HIGH);
  rSignal();
  digitalWrite(LB, LOW);
  digitalWrite(EA, LOW);
  digitalWrite(MUL, HIGH);
  rSignal();
  digitalWrite(MUL, LOW);
  digitalWrite(EU, HIGH);
  digitalWrite(LA, HIGH);
  rSignal();
  digitalWrite(LA, LOW);
  digitalWrite(EU, LOW);
  //PC++;
}

void goTo() {
  
  //Recordar la salida del puerto al bus.
  saved_PC = PC;
  did_goto = true;
  digitalWrite(EI,HIGH);
  digitalWrite(LA,HIGH);
  rSignal();
  digitalWrite(LA, LOW);
  digitalWrite(EI, LOW);
  digitalWrite(EA,HIGH);
  digitalWrite(LI,HIGH);
  rSignal();
  digitalWrite(LI,LOW);
  digitalWrite(EA,LOW);
  PC = PINA;

}

void retrn() {

  if (did_goto) {
    PC = saved_PC;
  } else {
    PC++;
  }

}

void out() {
  digitalWrite(EA, HIGH);
  digitalWrite(LO, HIGH);
  rSignal();
  digitalWrite(LO, LOW);
  rSignal();
  digitalWrite(EA, LOW);
  //PC++;
}

void hlt() {
  while (true) {}
}

void clockSignal() {
  clkState = !clkState;
  digitalWrite(CLK, clkState);
}

void rSignal() {
  while (digitalRead(CLK) == LOW) {
  }
  while (digitalRead(CLK) == HIGH) {
  }
}

void err() {
  Serial.println("Uribe Presidente");
  while (true) {}
}

void setup() {
  // put your setup code here, to run once:

  PC = 0;

  pinMode(LM, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(EE, OUTPUT);
  pinMode(LI, OUTPUT);
  pinMode(EI, OUTPUT);
  pinMode(LA, OUTPUT);
  pinMode(EA, OUTPUT);
  pinMode(EU, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(LO, OUTPUT);
  pinMode(ADD, OUTPUT);
  pinMode(SUB, OUTPUT);
  pinMode(MUL, OUTPUT);
  pinMode(DIV, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(ECON, OUTPUT);

  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
  pinMode(28, INPUT);
  pinMode(29, INPUT);

  digitalWrite(LM, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(EE, LOW);
  digitalWrite(LI, LOW);
  digitalWrite(EI, LOW);
  digitalWrite(LA, LOW);
  digitalWrite(EA, LOW);
  digitalWrite(EU, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(LO, LOW);
  digitalWrite(ADD, LOW);
  digitalWrite(SUB, LOW);
  digitalWrite(MUL, LOW);
  digitalWrite(DIV, LOW);
  digitalWrite(CLK, LOW);
  digitalWrite(ECON, LOW);

  DDRL = B11111111;
  PORTL = 0;


  Timer1.initialize(16);
  Timer1.attachInterrupt(clockSignal);
  pinMode(ERRPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ERRPIN), err, LOW);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("PC: ");
  Serial.println(PC);
  PORTL = PC;
  digitalWrite(ECON, HIGH);
  PC++;
  digitalWrite(LM, HIGH);
  rSignal();
  digitalWrite(LM, LOW);
  digitalWrite(ECON, LOW);
  digitalWrite(CE, HIGH);
  digitalWrite(EE, HIGH);
  digitalWrite(LI, HIGH);
  rSignal();
  digitalWrite(LI, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(EE, LOW);
  Serial.print("PINA: ");
  Serial.println(PINA);
  switch (PINA) {
    case B00000001:
      Serial.println("LDA");
      lda();
      break;
    case B00000010:
      Serial.println("ADD");
      add();
      break;
    case B00000011:
      Serial.println("SUB");
      sub();
      break;
    case B00000100:
      Serial.println("DIV");
      divi();
      break;
    case B00000101:
      Serial.println("MUL");
      mul();
      break;
    case B00000110:
      Serial.println("PW2");
      pw2();
      break;
    case B00000111:
      Serial.println("OUT");
      out();
      break;
    case B00001000:
      Serial.println("GOTO");
      goTo();
      break;
    case B00001001:
      Serial.println("RETURN");
      retrn();
      break;
    case B00001010:
      Serial.println("HLT");
      hlt();
      break;
  }
}