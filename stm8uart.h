#ifndef __stm8uart_h__
#define __stm8uart_h__

#define uart_init(_uart, _baud_rate)                                             \
    {                                                                            \
        _uart.CR1.byte = 0;                                                      \
        _uart.CR2.byte = 0;                                                      \
        _uart.CR3.byte = 0;                                                      \
        uint16_t val16 = (uint16_t)(((uint32_t)STM8_FREQ) / _baud_rate);         \
        _uart.BRR2.byte = (uint8_t)(((val16 & 0xF000) >> 8) | (val16 & 0x000F)); \
        _uart.BRR1.byte = (uint8_t)((val16 & 0x0FF0) >> 4);                      \
        _uart.CR2.REN = 1;                                                       \
        _uart.CR2.TEN = 1;                                                       \
    }

#define uart_putc(_uart, _c)    \
    {                           \
        while (!(_uart.SR.TXE)) \
            ;                   \
        _uart.DR.byte = _c;     \
    }

#define uart_print(uart, str)            \
    {                                    \
        char *__str = str;               \
        while (*__str)                    \
            uart_putc(uart, *(__str++)); \
    }

#define uart_printf(uart, buf, fmt, ...) \
    {                                    \
        sprintf(buf, fmt, __VA_ARGS__);  \
        uart_print(uart, buf);           \
    }

/*

    _uart->CR1.byte = sfr_UART1_PSCR_RESET_VALUE; // enable UART, 8 data bits, no parity control
    _uart->CR2.byte = sfr_UART1_PSCR_RESET_VALUE; // no interrupts, disable sender/receiver
    _uart->CR3.byte = sfr_UART1_PSCR_RESET_VALUE; // no LIN support, 1 stop bit, no clock output(?)

    // set baudrate (note: BRR2 must be written before BRR1!)
    // WORD val16 = (uint16_t)(((uint32_t)16000000L) / baudRate);
    uint16_t val16 = (uint16_t)(((uint32_t)2000000L) / baudRate);
    _uart->BRR2.byte = (uint8_t)(((val16 & 0xF000) >> 8) | (val16 & 0x000F));
    _uart->BRR1.byte = (uint8_t)((val16 & 0x0FF0) >> 4);

    // enable transmission, no transmission
    _uart->CR2.REN = 1; // enable receiver
    _uart->CR2.TEN = 1; // enable sender
    // uart->CR2.TIEN = 1;  // enable transmit interrupt
    // uart->CR2.RIEN = 1; // enable receive interrupt

*/

/*
#include <config.h>

void uartBegin(uint32_t baudRate);
void uartPrint(const char *msg);
void uartPrintSymbol(const char sym, size_t count);

#define uartPrintf(buf, fmt, ...)                     \
    {                                            \
        sprintf(buf, fmt, __VA_ARGS__); \
        uartPrint(buf);                 \
    }
*/

#endif