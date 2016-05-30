#define R_LED 1
#define Y_LED 2
#define G_LED 3

void InitLED();
void OnLED(unsigned char color);
void OffLED(unsigned char color);
void Delay(unsigned long delay);