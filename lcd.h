
#define CTRL        0
#define DATA        1

void print(char string[]);
void writeNibbleLcd(bool reg, char data);
void writeLcd(bool reg, char data);
void waitLcd(void);
void initLcd(void);
