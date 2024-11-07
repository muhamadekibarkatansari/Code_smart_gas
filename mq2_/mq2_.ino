const int mq2Pin = 33;       // Pin ADC untuk MQ-2 di ESP32 (gunakan GPIO 33)
const int relay1Pin = 18;    // Relay 1
const int relay2Pin = 19;    // Relay 2
const int redPin = 27;       // Pin untuk LED Merah
const int yellowPin = 26;    // Pin untuk LED Kuning
const int greenPin = 25;     // Pin untuk LED Hijau
const int buzzerPin = 15;    // Pin untuk Buzzer
int threshold = 200;         // Ambang batas asap

void setup() {
  Serial.begin(9600); // Memulai komunikasi serial
  
  pinMode(mq2Pin, INPUT);       // Set pin MQ-2 sebagai input
  pinMode(relay1Pin, OUTPUT);   // Set pin relay 1 sebagai output
  pinMode(relay2Pin, OUTPUT);   // Set pin relay 2 sebagai output
  pinMode(redPin, OUTPUT);      // Set pin LED Merah sebagai output
  pinMode(yellowPin, OUTPUT);   // Set pin LED Kuning sebagai output
  pinMode(greenPin, OUTPUT);    // Set pin LED Hijau sebagai output
  pinMode(buzzerPin, OUTPUT);   // Set pin buzzer sebagai output

  // Memastikan relay, LED, dan buzzer dalam keadaan mati saat memulai
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
  turnOffLEDs();                // Mematikan semua LED
  noTone(buzzerPin);            // Memastikan buzzer mati
}

void loop() {
  int smokeValue = analogRead(mq2Pin); // Membaca nilai sensor MQ-2
  Serial.print("Nilai Gas: ");
  Serial.println(smokeValue);          // Menampilkan nilai asap di Serial Monitor
  
  if (smokeValue > threshold) {
    digitalWrite(relay1Pin, HIGH);    // Aktifkan Relay 1
    digitalWrite(relay2Pin, HIGH);    // Aktifkan Relay 2
    tone(buzzerPin, 100);             // Mengeluarkan suara buzzer
    setLEDColor("RED");               // Merah - asap terdeteksi
    Serial.println("Gas terdeteksi!!!!");
  } else if (smokeValue > threshold - 50) {
    digitalWrite(relay1Pin, LOW);
    digitalWrite(relay2Pin, LOW);
    noTone(buzzerPin);                // Memastikan buzzer mati
    setLEDColor("YELLOW");            // Kuning - kadar asap mendekati batas
    Serial.println("Gas mendekati ambang batas.");
  } else {
    digitalWrite(relay1Pin, LOW);     // Matikan Relay 1
    digitalWrite(relay2Pin, LOW);     // Matikan Relay 2
    noTone(buzzerPin);                // Mematikan buzzer
    setLEDColor("GREEN");             // Hijau - tidak ada asap
    Serial.println("Tidak ada Gas.");
  }
  
  delay(1000); // Delay untuk pembacaan setiap detik
}

// Fungsi untuk mematikan semua LED
void turnOffLEDs() {
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
}

// Fungsi untuk mengatur warna LED
void setLEDColor(String color) {
  turnOffLEDs(); // Memastikan hanya satu LED yang menyala
  if (color == "RED") {
    digitalWrite(redPin, HIGH);
  } else if (color == "YELLOW") {
    digitalWrite(yellowPin, HIGH);
  } else if (color == "GREEN") {
    digitalWrite(greenPin, HIGH);
  }
}
