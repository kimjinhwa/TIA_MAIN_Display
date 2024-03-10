#ifndef MAIN_H
#define MAIN_H

typedef struct _initialRomData
{
    uint16_t HighVoltage;
    uint16_t LowVoltage;
    uint16_t HighTemp;
    uint16_t HighImp;
    uint16_t alarmSetStatus;
} initialRomData;

#endif