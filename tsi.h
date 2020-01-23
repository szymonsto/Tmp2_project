#include "MKL05Z4.h"

int tsi_scan(int offset);
int tsi_init(void);

#define SCAN_DATA TSI0_DATA & 0xFFFF // Accessing the bits held in TSI0_DATA

