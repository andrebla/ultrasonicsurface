const int pingPin = 14;
const int led[4] = { 6, 8, 9, 10};
const int button = 5;
int cmax;

long leitura() {
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = duration /29 / 2;
 
  Serial.println(cm);
  delay(50);
  
  return(cm);
}

void indicador(int c) {
  if(c > 0 && c < cmax / 4) {
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
  }
  if(c > cmax / 4 && c < 2 * cmax / 4) {
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
  }
  if(c > 2 * cmax / 4 && c < 3 *cmax / 4) {
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], LOW);
  }
  if(c > 3 * cmax / 4 && c < cmax - 1) {
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], HIGH);
  }
  if(c > cmax - 1) {
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
  }
}

void setup() {
  for(int i = 0; i < 4; i++) {
    pinMode(led[i], OUTPUT);
  }
  pinMode( button, INPUT);
  Serial.begin(9600);
  Keyboard.begin();
  cmax = leitura();
}
 
void loop() {
  int valor = (leitura());
  while(digitalRead(button)) {
    int valor = (leitura());
    indicador(valor);
  }
  if(valor < cmax - 1) {
    Keyboard.write(map(valor, 1, cmax - 1, 65, 90));
  }
}
