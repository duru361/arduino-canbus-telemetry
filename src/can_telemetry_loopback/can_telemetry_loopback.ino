#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

const int TRIG_PIN = 3;
const int ECHO_PIN = 4;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("--- CAN LOOPBACK TESTI BASLIYOR ---");

  // 8MHz ile başlat
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    CAN.setMode(MCP_LOOPBACK);
    Serial.println("CAN: Loopback modunda hazir!");
  } else {
    Serial.println("CAN: Baslatma hatasi!");
    while (1);
  }
}

void loop() {
  // 1. Ultrasonik Sensör Ölçümü
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long sure = pulseIn(ECHO_PIN, HIGH, 30000);
  byte mesafe = 0;
  if (sure > 0) {
    mesafe = sure * 0.034 / 2;
  }

  // 2. CAN ile Gönder (ID: 0x101, 1 Bayt Veri: Mesafe)
  byte txData[1] = {mesafe};
  byte txDurum = CAN.sendMsgBuf(0x101, 0, 1, txData);

  // 3. CAN'den Geri Oku
  long unsigned int rxId = 0;
  unsigned char len = 0;
  unsigned char rxBuf[8];
  bool paketVar = false;

  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    CAN.readMsgBuf(&rxId, &len, rxBuf);
    paketVar = true;
  }

  // 4. Seri Port Çıktısı
  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.print(" cm | Tx: ");
  Serial.print(txDurum == CAN_OK ? "OK" : "ERR");

  if (paketVar) {
    Serial.print(" | Rx: [ID: 0x");
    Serial.print(rxId, HEX);
    Serial.print(" -> Mesafe: ");
    Serial.print(rxBuf[0]);
    Serial.println(" cm]");
  } else {
    Serial.println(" | Rx: Bekleniyor...");
  }

  delay(300);
}