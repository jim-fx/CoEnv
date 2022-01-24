#include <iomanip>
#include <sstream>
#include <unistd.h>

#include "MFRC522.h"
#include <liquidcrystal/LiquidCrystal_I2C.h>

int main() {

  // GPIO chip i2c address
  u_int8_t i2c = 0x27;

  // Control line PINs
  u_int8_t en = 2;
  u_int8_t rw = 1;
  u_int8_t rs = 0;

  // Data line PINs
  u_int8_t d4 = 4;
  u_int8_t d5 = 5;
  u_int8_t d6 = 6;
  u_int8_t d7 = 7;

  // Backlight PIN
  u_int8_t bl = 3;

  // LCD display size (1x16, 2x16, 4x20)
  u_int8_t rows = 2;
  u_int8_t cols = 16;

  int adapter_nr = 1;
  char filename[20];

  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);

  printf("Using i2c device: %s, Rows: %u, Cols: %u\n", filename, rows, cols);

  LiquidCrystal_I2C lcd(filename, i2c, en, rw, rs, d4, d5, d6, d7, bl,
                        POSITIVE);

  lcd.begin(cols, rows);

  MFRC522 mfrc;

  mfrc.PCD_Init();

  while (true) {
    // Look for a card
    if (!mfrc.PICC_IsNewCardPresent())
      continue;

    if (!mfrc.PICC_ReadCardSerial())
      continue;

    // Print UID
    for (byte i = 0; i < mfrc.uid.size; ++i) {

      if (mfrc.uid.uidByte[i] < 0x10) {
        printf(" 0");
        printf("%X", mfrc.uid.uidByte[i]);
      } else {
        printf(" ");
        printf("%X", mfrc.uid.uidByte[i]);
      }
    }
    printf("\n");

    char hexstr[mfrc.uid.size * 2 + 1];
    int i;
    for (i = 0; i < mfrc.uid.size; i++) {
      sprintf(hexstr + i * 2, "%02x", mfrc.uid.uidByte[i]);
    }
    hexstr[i * 2] = 0;

    lcd.clear();
    lcd.print(hexstr);

    // Sleep for a second
    usleep(1000 * 1000);
  }
  return 0;
}
