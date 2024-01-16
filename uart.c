#ifndef __uart_h__
#define __uart_h__

#include <config.h>

void uartBegin(uint32_t baudRate);
void uartPrint(const char *msg);
void uartPrintSymbol(const char sym, size_t count);

#define uartPrintf(buf, fmt, ...)                     \
    {                                            \
        sprintf(buf, fmt, __VA_ARGS__); \
        uartPrint(buf);                 \
    }

#endif