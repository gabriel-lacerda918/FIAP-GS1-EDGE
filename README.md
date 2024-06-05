# Sistema de Monitoramento de Qualidade da Água - **OceanGuard**

![Technologies](https://img.shields.io/badge/Arduino-Uno-blue) ![Technologies](https://img.shields.io/badge/Language-C++-brightgreen) ![Technologies](https://img.shields.io/badge/Simulator-Tinkercad-orange)

## Projeto

Este projeto simula um sistema de monitoramento da qualidade da água para promover a sustentabilidade dos oceanos. Utilizando o Arduino Uno, o sistema lê dados de sensores de pH, temperatura e salinidade, e utiliza LEDs para indicar as condições da água. A simulação é realizada via <a href="https://www.tinkercad.com/" target="_blank">Tinkercad</a>.

## Componentes Utilizados

- **Arduino Uno**
- **Potenciômetro** (Simular Sensor de pH)
- **Sensor de Temperatura TMP36**
- **Potenciômetro** (Simular Sensor de Salinidade)
- **LEDs** (Verde, Amarelo, Vermelho)
- **Resistores (220Ω)**
- **Jumpers e Protoboard**

## Imagem do Circuito Simulado
![Circuito-TinkerCad](https://github.com/gabriel-lacerda918/FIAP-GS1-EDGE/assets/161903643/6b0fa45d-cbe3-4465-90a3-a8d5b41b6fe3)

<a href="https://www.tinkercad.com/things/dTAvkkiNOE5-oceanguard?sharecode=98YUdb45gF1hmsfvKP137msdEhov3IQXA2KcbNiIIqc" target="_blank">Link para visualização do projeto - Tinkercad</a>

## Funcionamento do Sistema

O sistema lê dados dos sensores para monitorar a qualidade da água do oceano. Baseado nas leituras de pH, temperatura e salinidade, os LEDs indicam se as condições estão dentro dos parâmetros ideais. Se duas ou mais leituras estiverem fora dos parâmetros ideais, um LED vermelho acende para indicar um problema geral.

### Condições Ideais

- **pH da Água:** entre 6 e 8
- **Temperatura da Água:** entre 25°C e 28°C
- **Salinidade:** entre 31 e 37 ppt

### Controle dos LEDs

- **LED Verde:** Indica que o parâmetro está dentro do valor ideal.
- **LED Amarelo:** Indica que o parâmetro está fora do valor ideal.
- **LED Vermelho:** Acende se duas ou mais leituras estiverem fora do valor ideal.

## Explicação do Código

### Definição dos Pinos dos Sensores e LEDs

```cpp
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
#define RED_LED_PIN
```

Importância: Este bloco define as conexões físicas entre os sensores/atuadores e o Arduino, facilitando a leitura dos valores e o controle dos LEDs.
<br>
### Configuração das Entradas e Saídas

```cpp
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
```

Importância: Este bloco inicializa a comunicação serial e configura os pinos dos LEDs como saídas, permitindo que o Arduino controle os LEDs com base nos dados dos sensores.
<br>
### Leitura dos Sensores
```cpp
void loop() {
  // Leitura do potenciômetro que simula o sensor de pH
  int phValue = analogRead(PH_PIN);
  float ph = map(phValue, 0, 1023, 0, 14); // Mapeia a leitura do potenciômetro para valores de 0 a 14
  
  // Leitura do sensor de temperatura TMP36
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
```
Importância: Este bloco lê os valores dos sensores e converte-os para unidades significativas (pH, temperatura em graus Celsius e salinidade em ppt). Também imprime os valores no monitor serial para depuração.

<br>
### Controle dos LEDs

```cpp
  // Variáveis de controle
  bool phIdeal = (ph >= 6.0 && ph <= 8.0);
  bool tempIdeal = (temperature >= 25.0 && temperature <= 28.0);
  bool salinityIdeal = (salinity >= 31.0 && salinity <= 37.0);
  int outOfRangeCount = 0;

  // Controle de LEDs para pH
  if (phIdeal) {
    digitalWrite(PH_GREEN_LED_PIN, HIGH);
    digitalWrite(PH_YELLOW_LED_PIN, LOW);
  } else {
    digitalWrite(PH_GREEN_LED_PIN, LOW);
    digitalWrite(PH_YELLOW_LED_PIN, HIGH);
    outOfRangeCount++;
  }

  // Controle de LEDs para temperatura
  if (tempIdeal) {
    digitalWrite(TEMP_GREEN_LED_PIN, HIGH);
    digitalWrite(TEMP_YELLOW_LED_PIN, LOW);
  } else {
    digitalWrite(TEMP_GREEN_LED_PIN, LOW);
    digitalWrite(TEMP_YELLOW_LED_PIN, HIGH);
    outOfRangeCount++;
  }

  // Controle de LEDs para salinidade
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

  delay(5000); // Aguardar 5 segundos antes da próxima leitura
}
```

Importância: Este bloco controla os LEDs com base nas leituras dos sensores. Se os valores dos sensores estiverem dentro dos limites ideais, os LEDs verdes são acesos; caso contrário, os LEDs amarelos acendem. Se duas ou mais leituras estiverem fora dos limites ideais, o LED vermelho é aceso para indicar um problema geral.
<br>
## Importância do Projeto
Este projeto visa monitorar e manter as melhores condições da água dos oceanos, promovendo a sustentabilidade. A qualidade da água é essencial para a vida marinha e a saúde do ecossistema oceânico. O monitoramento constante pode ajudar a identificar e mitigar problemas antes que eles causem danos significativos, contribuindo para a preservação dos oceanos e a promoção de uma economia azul sustentável.
<br>
## Autores

Este projeto foi desenvolvido por:

Gabriel Machado Lacerda RM: 556714

Roger Cardoso Ferreira RM: 557230

TURMA: 1ESPW
