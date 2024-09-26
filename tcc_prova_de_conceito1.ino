
#include <LiquidCrystal.h> // Importa a biblioteca LCD
LiquidCrystal LCD(10, 9, 5, 4, 3, 2); // Inicializa os pinos do LCD
#include <Servo.h> // Importa a biblioteca Servo

// Define as notas que serão tocadas
#define N_D3  147 
#define N_DS3 156
#define N_E3  165
#define N_F3  175
#define N_FS3 185
#define N_G3  196
#define N_GS3 208
#define N_A3  220
#define N_AS3 233
#define N_B3  247
#define N_C4  262
#define N_CS4 277
#define N_D4  294

// Inicializa as variáveis relacionadas ao sensor ultrassônico
int trigPin = A1; // Inicializa o pino do trig
int echoPin = A0; // Inicializa o pino do echo
float pingTime; // Inicializa a variável pingTime
float targetDistance; // Inicializa a variável targetDistance 

// Inicializa as variáveis relacionadas ao botão
int buttonPin = 11; // Inicializa o pino do botão
int in11; // Inicializa a variável para ler o estado do botão
int buttonOnOff = 0; // Inicializa a variável buttonOnOff

// Inicializa as variáveis relacionadas ao alto-falante e à música
int piezo = 6; // Inicializa o pino do piezo
int tempo = 1200; // Define o tempo para 1200 bpm
int melody[] = {N_D3, N_D3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3}; // Inicializa um array de notas para a música
int durations[] = {16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16}; // Inicializa um array com as durações de cada nota
int noteDuration; // Inicializa a variável noteDuration
int notePause; // Inicializa a variável notePause
int melodyLength = sizeof(melody)/sizeof(melody[0]); // Inicializa o comprimento da melodia

// Inicializa todas as outras variáveis necessárias
int servoPin = A2; // Inicializa o pino do servo
int led = 7; // Inicializa o pino do LED

Servo servo; // Inicializa o servo

void setup() // Função usada para configurar os pinos, iniciar o serial e conectar os servos
{
  Serial.begin(9600); // Inicia o serial na frequência 9600
  pinMode(piezo, OUTPUT); // Define o piezo como saída
  pinMode(led, OUTPUT); // Define o LED como saída
  pinMode(trigPin, OUTPUT); // Define o trigPin como saída
  pinMode(echoPin, INPUT); // Define o echoPin como entrada
  delay(250); // Atraso de 150 milissegundos
  pinMode(buttonPin, INPUT); // Define o botão como entrada
  servo.attach(servoPin); // Conecta o pino do servo
  LCD.begin(16, 2); // Inicia o LCD
  LCD.setCursor(0, 0); // Define o cursor do LCD 
}

void checkDistance(){ // Função usada para detectar a distância
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  pingTime = pulseIn(echoPin, HIGH);
  targetDistance = 0.034 * pingTime / 2;
}

void blink(){ // Função usada para fazer o LED piscar
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
}

void alert(){ // Função usada para tocar a música
  for (int current = 0; current < melodyLength; current++){ // Cria um loop para tocar as notas da música
    noteDuration = tempo/durations[current]; // Define a duração da nota com base no tempo e nas durações das notas
    tone(piezo, melody[current], noteDuration); // Toca a nota
    notePause = noteDuration * 1.45; // Define a pausa entre as notas
    delay(notePause); // Atraso
    noTone(piezo); // Desativa o piezo
  }
}

void countDown(int timer){ // Função usada para fazer a contagem regressiva no LCD
  int loopCount = timer;
  for (int i = 0; i <= loopCount; i++){
    resetDisplay();
    LCD.setCursor(0, 0);
    LCD.print("Status: Aguardando");
    LCD.setCursor(0, 1);
    LCD.print("Cooldown: ");
    LCD.print(timer);
    timer = timer - 1;
    delay(1000);
  }
  resetDisplay();
}

void displayDistance(){ // Função usada para exibir a distância e imprimir informações
   LCD.setCursor(0, 0); 
   LCD.print("Status: Em espera ");
   LCD.setCursor(0,1);
   LCD.print("Distancia: ");
   LCD.print(targetDistance);
   LCD.print(" cm");
}

void resetDisplay(){ // Função usada para resetar o display
  LCD.setCursor(0,0);
  LCD.print("                 "); // Limpa a primeira linha
  LCD.setCursor(0,1);
  LCD.print("                 "); // Limpa a segunda linha
}

void loop() // Função principal do código
{
  in11 = digitalRead(buttonPin); // Lê o botão
  delay(1000); // Atraso de 1 segundo
  if (in11 == HIGH){ // Se o botão estiver em nível alto
    if (buttonOnOff == 0){ // Se o estado de buttonOnOff for 0, muda para 1
      buttonOnOff = 1; 
      Serial.print("Inativo");
    }
    else if(buttonOnOff == 1){ // Se o estado de buttonOnOff for 1, muda para 0
      buttonOnOff = 0;
      Serial.print("Ativo");
    }
  }
  if (buttonOnOff == 0){ // Se o estado de buttonOnOff for 0
    checkDistance(); // Checa a distância
    displayDistance(); // Exibe a distância
    if (targetDistance <= 25){ // Se a targetDistance for menor ou igual a 25
      resetDisplay(); // Reseta o display
      LCD.setCursor(0, 0);
      LCD.print("Status: Ativo");
      LCD.setCursor(0, 1);
      LCD.print("Dispensando");
      alert(); // Toca o Alerta
      servo.write(0); // Move o servo
      blink(); // Faz o LED piscar
      servo.write(90);
      countDown(5); // Faz a contagem regressiva
      checkDistance(); // Checa a distância novamente
    }
    else{
      servo.write(90); // Reseta o servo e o LED
      digitalWrite(led,LOW);
    }
  }
  else if (buttonOnOff == 1){ // Se o estado de buttonOnOff for 1
    servo.write(90); // Reseta todos os componentes
    digitalWrite(led,LOW);
    LCD.setCursor(0, 0);
    LCD.print("Status: Inativo");
    LCD.setCursor(0, 1);
    LCD.print("                ");
  }
}
