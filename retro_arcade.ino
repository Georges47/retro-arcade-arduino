#define selectButtonPin 5
#define interruptPin 2
#define echoPin 7
#define trigPin 8
#define raspberryPiUltrasonicPin 12
#define raspberryPiCoinPin 13

long duration;
int distance;

int nonProcessedCoins = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(selectButtonPin , OUTPUT);
  digitalWrite(selectButtonPin , HIGH);
  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), incrementNonProcessedCoins, RISING);

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT); 
  pinMode(raspberryPiUltrasonicPin, OUTPUT);
  digitalWrite(raspberryPiUltrasonicPin, LOW);
  pinMode(raspberryPiCoinPin, OUTPUT);
  digitalWrite(raspberryPiCoinPin, LOW);
}

void loop() {
  // El sensor emite la onda de sonido
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lee echoPin, retorna el tiempo de viaje en microsegundos de la onda de sonido
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2; // cm
    
  // Avisa al RaspberryPi que la distancia calculada es menor a 50cm
  if(distance < 50) {
    digitalWrite(raspberryPiUltrasonicPin, HIGH);
  } else {
    digitalWrite(raspberryPiUltrasonicPin, LOW);
  }

  // Simula como si alguien hubiera apretado SELECT (agrega una moneda) y le envía
  // un pulso al RaspberryPi
  if(nonProcessedCoins > 0) {
    nonProcessedCoins--;
    
    digitalWrite(selectButtonPin, LOW);
    delay(500);
    digitalWrite(selectButtonPin, HIGH);
    
    if(digitalRead(raspberryPiCoinPin) == HIGH) {
    	digitalWrite(raspberryPiCoinPin, LOW);
    } else {
    	digitalWrite(raspberryPiCoinPin, HIGH);
    }
  }

  delay(250);
}

void incrementNonProcessedCoins () {
  nonProcessedCoins++;
}
