# ArduinoLightComm
Transmita dados usando luz com Arduino!

Este projeto demonstra como usar um Arduino para enviar e receber informações através de pulsos luminosos, utilizando um LED como transmissor e um sensor LDR como receptor. Com essa abordagem, é possível criar um sistema de comunicação simples e eficiente baseado em luz.

## 🚀 Funcionalidades
Envio de mensagens codificadas através de pulsos de luz
Decodificação automática dos sinais recebidos
Configuração personalizável de tempo de transmissão e sensibilidade do sensor
Exemplo de código pronto para rodar em qualquer Arduino compatível
## 🔧 Como funciona?
Cada letra da mensagem é convertida em um número correspondente, e o Arduino pisca o LED um número de vezes equivalente. No receptor, o sensor LDR detecta esses pulsos e reconstrói a mensagem original.

# 📦 Como usar
Monte o circuito com um LED para transmissão e um sensor LDR para recepção
Carregue o código no Arduino (tanto no transmissor quanto no receptor)
Envie uma mensagem e veja a magia acontecer!
## 🛠 Requisitos
Arduino Uno (ou compatível)
LED para transmissão
Sensor LDR para recepção
Resistores (dependendo do circuito)
## 📜 Código
O código principal está disponível no arquivo main.ino. Basta compilá-lo e enviá-lo para o seu Arduino!

## 🎥 Demonstração
Confira o vídeo explicativo no YouTube: [Video](https://www.youtube.com/watch?v=wWbI9BvpWtg)


## 🔌 Configuração dos Pinos
Pino 13 (Saída - LED Transmissor)

O LED que emite os pulsos de luz está conectado ao pino digital 13.
No código, este pino é definido como saída:
```c#
int PIN_LED = 13;
pinMode(PIN_LED, OUTPUT);
```
Quando o Arduino quer enviar uma informação, ele liga e desliga o LED rapidamente, criando pulsos de luz.
```c#
Pino A0 (Entrada - LDR Receptor)
```
O sensor LDR (Light Dependent Resistor) está conectado à entrada analógica A0.
No código, o valor do sensor é lido usando:
```c#
int LDR = analogRead(A0);
```
O Arduino verifica se a luz está presente analisando o valor do LDR.
Um limiar (>= 700) é utilizado para identificar quando a luz do LED foi recebida:
```c#
return LDR >= 700;
```
## 🛠 Como o Esquema Funciona?
Transmissão: O Arduino pisca o LED um número de vezes correspondente à letra que está sendo enviada.
Recepção: O LDR detecta esses pulsos de luz e o Arduino os converte de volta para letras, reconstruindo a mensagem.
Sincronização: Um tempo de intervalo entre letras (letterGapThreshold) ajuda o receptor a separar os caracteres corretamente.
