#define PIR_PIN       PA0
#define TRIG_PIN      PA1
#define ECHO_PIN      PA4
#define BUZZER_PIN    PB0

long duration;
int distance;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(BUZZER_PIN, LOW);

  // Serial monitor untuk pengecekan data
  Serial.begin(115200);
  Serial.println("--- Sistem Keamanan Bertingkat STM32 Ready ---");
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout 30ms
  if (duration == 0) return 999;
  
  return duration * 0.034 / 2; // Konversi pulsa ke cm
}

void loop() {
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    distance = getDistance();
    
    Serial.print("Gerakan Terdeteksi! Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance <= 10) {
      // Bahaya (Sangat Dekat) -> Bunyi Panjang
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
    } 
    else if (distance > 10 && distance <= 30) {
      // Peringatan (Mendekat) -> Bip Lambat
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);
      delay(200);
    } 
    else {
      digitalWrite(BUZZER_PIN, LOW);
    }
  } 
  else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(50);
}