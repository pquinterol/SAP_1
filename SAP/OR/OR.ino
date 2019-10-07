#define pinSg 50
#define ERRPIN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(27, INPUT);
  pinMode(28, INPUT);
  pinMode(29, INPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(pinSg, OUTPUT);
  
  pinMode(ERRPIN, INPUT_PULLUP);
  
  PORTL = 0;
  attachInterrupt(digitalPinToInterrupt(ERRPIN), err, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  mostrar(PINA);
}

void mostrar(byte num) {
  bool sg = bitRead(num, 7);
  num = sg ? complementoDos(num) : num;
  byte dNum = (num / 10) << 4;
  byte uNum = num % 10;
  digitalWrite(pinSg,sg);
  PORTL = dNum | uNum;
}

byte complementoDos(byte num) {
  return (~num) + 1;
}

void err(){
  PORTL = B11101110;
  while (digitalRead(ERRPIN) == LOW){}
  PORTL = B00000000;
}
