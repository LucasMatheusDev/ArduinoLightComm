int PIN_LED = 13;
int INTERVALO_BITS_MS = 30;
const unsigned long letterGapThreshold = 200;  // Ajuste conforme necessário

// Função para obter o índice da letra
int getIndice(char letra) {
  letra = toupper(letra);
  if (letra >= 'A' && letra <= 'Z') {
    return letra - 'A' + 1;
  }
  return -1;
}

// Função para converter índice em letra
char getLetra(int indice) {
  if (indice >= 1 && indice <= 26) {
    return 'A' + indice - 1;
  }
  return '\0';
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  Serial.println("Iniciando Leitura");
}

// Verifica se a leitura do LDR indica pulso (ajuste o valor conforme a sensibilidade do sensor)
bool isLDRValid() {
  int LDR = analogRead(A0);
  return LDR >= 700;
}

// Variáveis para o receptor
int CONTAGEM_BITS = 0;
String ULTIMA_MSG = "";
unsigned long lastPulseTime = 0;
bool pulsoAnterior = false;  // Variável para detecção de borda

void sendMessage(String msg) {
  // Transmissor: para cada letra, envia a quantidade de pulsos correspondente
  for (int idx = 0; idx < msg.length(); idx++) {
    char letra = msg.charAt(idx);
    int indice = getIndice(letra);
    Serial.print("Enviando letra: ");
    Serial.print(letra);
    Serial.print(" com ");
    Serial.print(indice);
    Serial.println(" pulsos");

    // Envia os pulsos correspondentes
    for (int j = 0; j < indice; j++) {
      digitalWrite(PIN_LED, HIGH);
      delay(INTERVALO_BITS_MS);
      digitalWrite(PIN_LED, LOW);
      delay(INTERVALO_BITS_MS);
    }
    // Delay extra para delimitar o fim da letra
    delay(letterGapThreshold);
  }
}

void readMessage() {
  unsigned long currentTime = millis();
  bool pulsoAtual = isLDRValid();
  int diferenciaDeTempo = currentTime - lastPulseTime;

  if (diferenciaDeTempo > 1000 && !pulsoAtual && ULTIMA_MSG != "" && CONTAGEM_BITS == 0) {
    Serial.print("Tempo: ");
    Serial.println(currentTime - lastPulseTime);
    Serial.print("Diferencia Tempo: ");
    Serial.println(diferenciaDeTempo);
    Serial.print("New Tempo: ");
    Serial.println(1000);
    Serial.print("Ultima info ");
    Serial.println(ULTIMA_MSG);
    ULTIMA_MSG = "";
  }

  // Detecta a borda de subida: conta somente na transição de "não pulso" para "pulso"
  if (pulsoAtual && !pulsoAnterior) {
    lastPulseTime = currentTime;
    CONTAGEM_BITS++;
    Serial.print("Pulso detectado. Contagem atual: ");
    Serial.println(CONTAGEM_BITS);
  }



  // Atualiza o estado anterior
  pulsoAnterior = pulsoAtual;

  // Se não houver pulso e passou o intervalo de gap, finaliza a letra
  if (CONTAGEM_BITS > 0 && (currentTime - lastPulseTime >= letterGapThreshold)) {

    char letraDecodificada = getLetra(CONTAGEM_BITS);
    ULTIMA_MSG += letraDecodificada;

    CONTAGEM_BITS = 0;
    Serial.print("Letra decodificada: ");
    Serial.println(letraDecodificada);
    Serial.print("Mensagem atual: ");
    Serial.println(ULTIMA_MSG);
  }
}

void loop() {
  bool isReceptor = true;
  if (isReceptor) {
    readMessage();
    delay(5);
  } else {
    sendMessage("arduino");
    delay(5000);
  }
}
