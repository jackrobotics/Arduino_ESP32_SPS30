/**
 * Mod By Sonthaya Boonchan @HONEYLab
 * Blog : https://www.jackrobotics.me
 * Website HONEYLab : https://www.honey-lab.com
 **/

/*************************************************/

#include "HardwareSerial.h"
HardwareSerial SERIALDEVICE_SPS30(2);
#define PIN_UART_RX 16
#define PIN_UART_TX 17

/*************************************************/

#include <Arduino.h>
#ifdef __cplusplus
  extern "C" {
#endif
#include "sensirion_arch_config.h"
#define BAUDRATE 115200  // baud rate of SPS30


s16 sensirion_uart_open() {
#ifdef USE_HARDWARE_SERIAL_ESP32
    SERIALDEVICE_SPS30.begin(BAUDRATE,SERIAL_8N1,PIN_UART_RX,PIN_UART_TX);
#endif
#ifdef USE_SOFTWARE_SERIAL_ARDUINO
    SERIALDEVICE_SPS30.begin(BAUDRATE);
#endif
    return 0;
}
s16 sensirion_uart_close() {
    SERIALDEVICE_SPS30.end();
    return 0;
}
s16 sensirion_uart_tx(u16 data_len, const u8 *data) {
    return SERIALDEVICE_SPS30.write(data, data_len);
}
s16 sensirion_uart_rx(u16 max_data_len, u8 *data) {
    s16 i = 0;
    while (SERIALDEVICE_SPS30.available() > 0 && i < max_data_len) {
        data[i] = (u8)SERIALDEVICE_SPS30.read();
        i++;
    }
    return i;
}
void sensirion_sleep_usec(u32 useconds) {
    delay((useconds / 1000) + 1);
}
#ifdef __cplusplus
}
#endif