#ifndef UTILITY_H
#define UTILITY_H

void parseDelayCommandPayload(const char *);
bool readMessage(int, char *, float *, float *);
bool readMessage(char *);

void SensorInit(void);

void blinkLED(void);
void blinkSendConfirmation(void);

#endif /* UTILITY_H */
