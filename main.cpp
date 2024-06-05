// Definindo pinos dos sensores
#define PH_PIN A0
#define SALINITY_PIN A1
#define TEMP_PIN A2

// Definindo pinos dos LEDs
#define PH_GREEN_LED_PIN 3
#define PH_YELLOW_LED_PIN 4
#define TEMP_GREEN_LED_PIN 5
#define TEMP_YELLOW_LED_PIN 6
#define SALINITY_GREEN_LED_PIN 7
#define SALINITY_YELLOW_LED_PIN 8
#define RED_LED_PIN 9

void setup() {
  Serial.begin(9600);

  // Configuração dos pinos dos LEDs
  pinMode(PH_GREEN_LED_PIN, OUTPUT);
  pinMode(PH_YELLOW_LED_PIN, OUTPUT);
  pinMode(TEMP_GREEN_LED_PIN, OUTPUT);
  pinMode(TEMP_YELLOW_LED_PIN, OUTPUT);
  pinMode(SALINITY_GREEN_LED_PIN, OUTPUT);
  pinMode(SALINITY_YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
  // Leitura do potenciômetro que simula o sensor de pH
  int phValue = analogRead(PH_PIN);
  float ph = map(phValue, 0, 1023, 0, 14); // Mapeia a leitura do potenciômetro para valores de 0 a 14
  
  // Leitura do sensor de temperatura TMP
  int tempValue = analogRead(TEMP_PIN);
  float voltage = tempValue * (5.0 / 1023.0); // Convertendo para volts
  float temperature = (voltage - 0.5) * 100; // Convertendo volts para graus Celsius
  
  // Leitura do potenciômetro que simula o sensor de salinidade
  int salinityValue = analogRead(SALINITY_PIN);
  float salinity = map(salinityValue, 0, 1023, 0, 100); // Mapeia a leitura do potenciômetro para valores de 0 a 100 ppt (simulado)

  // Imprimir valores no Serial Monitor
  Serial.print("pH: ");
  Serial.print(ph);
  if (ph < 6.0) {
    Serial.print(" (Ácido)");
  } else if (ph > 8.0) {
    Serial.print(" (Alcalino)");
  } else {
    Serial.print(" (Neutro)");
  }
  
  Serial.print(" | Temperatura: ");
  Serial.print(temperature);
  
  Serial.print("C | Salinidade: ");
  Serial.print(salinity);
  Serial.println(" ppt");
  
  Serial.println("---");

  // Variáveis de controle
  bool phIdeal = (ph >= 6.0 && ph <= 8.0);
  bool tempIdeal = (temperature >= 21.0 && temperature <= 28.0);
  bool salinityIdeal = (salinity >= 31.0 && salinity <= 37.0);
  int outOfRangeCount = 0;

  // Controle de LEDs - pH
  if (phIdeal) {
    digitalWrite(PH_GREEN_LED_PIN, HIGH);
    digitalWrite(PH_YELLOW_LED_PIN, LOW);
  } else {
    digitalWrite(PH_GREEN_LED_PIN, LOW);
    digitalWrite(PH_YELLOW_LED_PIN, HIGH);
    outOfRangeCount++;
  }

  // Controle de LEDs - temperatura
  if (tempIdeal) {
    digitalWrite(TEMP_GREEN_LED_PIN, HIGH);
    digitalWrite(TEMP_YELLOW_LED_PIN, LOW);
  } else {
    digitalWrite(TEMP_GREEN_LED_PIN, LOW);
    digitalWrite(TEMP_YELLOW_LED_PIN, HIGH);
    outOfRangeCount++;
  }

  // Controle de LEDs - salinidade
  if (salinityIdeal) {
    digitalWrite(SALINITY_GREEN_LED_PIN, HIGH);
    digitalWrite(SALINITY_YELLOW_LED_PIN, LOW);
  } else {
    digitalWrite(SALINITY_GREEN_LED_PIN, LOW);
    digitalWrite(SALINITY_YELLOW_LED_PIN, HIGH);
    outOfRangeCount++;
  }

  // Controle de LED vermelho
  if (outOfRangeCount >= 2) {
    digitalWrite(RED_LED_PIN, HIGH);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
  }

  delay(2500); // Aguardar 2.5 segundos entre as leituras
}
