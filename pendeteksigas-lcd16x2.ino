#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int analogPin = A0; // Pin analog sensor gas terhubung ke pin A0 pada Arduino
const int thresholdValue = 500; // Nilai ambang batas untuk mendeteksi gas (sesuaikan sesuai kebutuhan Anda)
const int ledPin = 4; // Pin LED terhubung ke pin 13 pada Arduino


// SDA ke pin A4 Arduino
// SCL ke pin A5 Arduino
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C LCD: 0x27 (sesuaikan dengan alamat LCD Anda)
 
void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial dengan kecepatan 9600 bps
  pinMode(ledPin, OUTPUT); // Mengatur pin LED sebagai OUTPUT
  lcd.begin(16, 2);      // Inisialisasi LCD 16x2
  lcd.backlight();       // Menghidupkan backlight LCD
}

void loop() {
  int sensorValue = analogRead(analogPin); // Membaca nilai analog dari sensor gas
  Serial.print("Nilai sensor gas: ");
  Serial.println(sensorValue); // Menampilkan nilai sensor gas ke Serial Monitor

  lcd.clear(); // Menghapus layar LCD
  lcd.setCursor(0, 0); // Pindahkan kursor ke baris pertama, kolom pertama
  lcd.print("Nilai Gas: ");
  lcd.print(sensorValue); // Menampilkan nilai sensor gas di LCD
  
  if (sensorValue > thresholdValue) {
    Serial.println("Gas terdeteksi!"); // Menampilkan pesan jika gas terdeteksi melebihi nilai ambang batas
    lcd.setCursor(0, 1); // Pindahkan kursor ke baris kedua, kolom pertama
    lcd.print("Gas Terdeteksi"); // Menampilkan pesan di LCD
    digitalWrite(ledPin, HIGH); // Menghidupkan LED ketika gas terdeteksi
  } else {
    Serial.println("Tidak ada gas terdeteksi."); // Menampilkan pesan jika gas tidak terdeteksi atau nilainya di bawah ambang batas
    lcd.setCursor(0, 1); // Pindahkan kursor ke baris kedua, kolom pertama
    lcd.print("Tidak Ada Gas"); // Menampilkan pesan di LCD
    digitalWrite(ledPin, LOW); // Mematikan LED ketika gas tidak terdeteksi
  }
  
  delay(1000); // Tunggu 1 detik sebelum membaca nilai sensor lagi
}
