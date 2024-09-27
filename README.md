# Prova de Conceito com Arduino

Este projeto é uma prova de conceito utilizando Arduino, que combina várias funcionalidades para demonstrar o uso de diferentes componentes eletrônicos. O sistema foi desenvolvido como parte de um trabalho de conclusão de curso (TCC) e serve para ilustrar conceitos de automação e interação com sensores.

## Funcionalidades

- **Display LCD**: Exibe informações ao usuário.
- **Servo Motor**: Realiza movimentos controlados programaticamente.
- **Sensor Ultrassônico**: Mede a distância de objetos próximos.
- **Botão**: Permite a interação do usuário com o sistema.
- **Alto-falante**: Toca notas musicais definidas no código.

## Componentes Utilizados

- Arduino Uno (ou compatível)
- Display LCD 16x2
- Servo motor
- Sensor ultrassônico (HC-SR04)
- Botão de pressão
- Alto-falante
- Resistores e jumpers conforme necessário

## Estrutura do Código

- **Configuração Inicial**: Definição de pinos e variáveis globais.
- **Loop Principal**: Lógica de operação, incluindo leitura do sensor, controle do servo, e reprodução de sons.
- **Funções Auxiliares**: Controle das operações do LCD, sensor e servo motor.

## Como Usar

1. Monte o circuito conforme o diagrama.

   ![image](https://github.com/user-attachments/assets/dd549cb9-296a-4a19-aafa-0f6817f1f185)

2. Carregue o código no seu Arduino.
3. Interaja com o sistema usando o botão e observe as leituras no LCD e o movimento do servo.
