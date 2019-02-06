/**
 * For example sps30 & esp32
 * Mod by Sonthaya Boonchan @HONEYLab
 * 05/02/2019
 * 
 * Hardware test
 * -> esp32 lite (mcu)
 * -> sps30 (sensor)
 * 
 * Communication uart
 * rx -> 16
 * tx -> 17
 * 
 * Please edit file sensirion_uart.cpp for change pin or port communication
*/

#include "sensirion_uart.h"
#include "sps30.h"

void setup() {
	Serial.begin(115200);
	sensirion_uart_open();

    while (sps30_probe() != 0) {
        Serial.println("probe failed");
        delay(1000);
    }
	// sps30_set_fan_auto_cleaning_interval(60*60);

    /* start measurement and wait for 10s to ensure the sensor has a
     * stable flow and possible remaining particles are cleaned out */
    if (sps30_start_measurement() != 0) {
        Serial.println("error starting measurement");
    }
}

void loop() {
    struct sps30_measurement measurement;
    s16 ret;

    while(true) {
        delay(1000);
        ret = sps30_read_measurement(&measurement);

        if (ret < 0) {
          Serial.println("read measurement failed");
        } else {
            if (SPS_IS_ERR_STATE(ret)) {
              Serial.println("Measurements may not be accurate");
            }else{
                Serial.print("pm1.0 :");Serial.println(measurement.mc_1p0);
                Serial.print("pm2.5 :");Serial.println(measurement.mc_2p5);
                Serial.print("pm4.0 :");Serial.println(measurement.mc_4p0);
                Serial.print("pm10.0 :");Serial.println(measurement.mc_10p0);
                Serial.print("nc0.5 :");Serial.println(measurement.nc_0p5);
                Serial.print("nc1.0 :");Serial.println(measurement.nc_1p0);
                Serial.print("nc2.5 :");Serial.println(measurement.nc_2p5);
                Serial.print("nc4.0 :");Serial.println(measurement.nc_4p0);
                Serial.print("nc10.0 :");Serial.println(measurement.nc_10p0);
                Serial.print("typical particle size :");Serial.println(measurement.typical_particle_size);
            }
        }
    }

    sps30_stop_measurement();
    sensirion_uart_close();
}
