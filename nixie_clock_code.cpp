#include <EEPROM.h>
#include <RTClib.h>
#include <Wire.h>

#define output_pins_count 16

RTC_DS3231 rtc;

uint8_t digit1_value = 0;
uint8_t digit2_value = 0;
uint8_t digit3_value = 0;
uint8_t digit4_value = 0;

uint8_t digit1_pins[3] = {3,4,5};
uint8_t digit2_pins[4] = {6,7,8,9};
uint8_t digit3_pins[4] = {10,11,12,13};
uint8_t digit4_pins[4] = {A0,A1,A2,A3};

uint8_t current_hour = 0;
uint8_t current_minute = 0;

bool daylight_savings;

const uint8_t indicator_light_pin = 2;

const int output_pins[output_pins_count] = {indicator_light_pin,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3};

void setup() {
    rtc.begin();

    for (int i=0;i<output_pins_count;i++) {
        pinMode(output_pins[i],OUTPUT);
    }

    // load daylight savings from EEPROM
    daylight_savings = EEPROM.get(0, daylight_savings) == 1;

    // Uncomment the following 2 lines if you need to set the DST (if you miss
    // the actual day etc). Change the +1 to -1 in the fall. DateTime t2 =
    // rtc.now(); rtc.adjust(DateTime(t2.year(), t2.month(), t2.day(),
    // t2.hour()+1, t2.minute(), t2.second()));
}

void loop() {
    DateTime time = rtc.now();

    if (time.dayOfTheWeek() == 0 &&
        time.month() == 3 &&
        time.day() >= 8 &&
        time.day() <= 16 &&
        time.hour() == 2 &&
        time.minute() == 0 &&
        time.second() == 0 &&
        !daylight_savings) {

        rtc.adjust(DateTime(
            time.year(),
            time.month(),
            time.day(),
            time.hour() + 1,
            time.minute(),
            time.second()
        ));

        flip_dst();
    } else if (time.dayOfTheWeek() == 0 &&
            time.month() == 11 &&
            time.day() >= 1 &&
            time.day() <= 8 &&
            time.hour() == 2 &&
            time.minute() == 0 &&
            time.second() == 0 &&
            daylight_savings) {

        rtc.adjust(DateTime(
            time.year(),
            time.month(),
            time.day(),
            time.hour() - 1,
            time.minute(),
            time.second()
        ));

        flip_dst();
    }

    // change state of indicator light every odd second
    uint8_t indicator_state = ((time.second() % 2) == 0) ? HIGH : LOW;
    digitalWrite(indicator_light_pin,indicator_state);

    current_minute = time.minute();
    current_hour = time.hour();

    // use pm time
    if (current_hour > 12) {
        current_hour = current_hour - 12;
    }

    // split individual multi-segment numbers into their individual segments
    digit1_value = (current_hour / 10) % 10;
    digit2_value = current_hour % 10;
    digit3_value = (current_minute / 10) % 10;
    digit4_value = current_minute % 10;

    // Configure digital outputs to nixie values
    write_binary(digit1_value,3,digit1_pins);
    write_binary(digit2_value,4,digit2_pins);
    write_binary(digit3_value,4,digit3_pins);
    write_binary(digit4_value,4,digit4_pins);

    // wait 200ms before updating the screen again
    delay(200);
}

void flip_dst() {
    daylight_savings = !daylight_savings;

    // encode DST as int and save into EEPROM
    EEPROM.put(0,daylight_savings ? 1 : 0);
}

void write_binary(uint8_t value,uint8_t pin_count,uint8_t pins[]) {
    for (int i=0;i<pin_count;i++) {
        int current_bit = (value >> i) & 1;

        digitalWrite(pins[i],(current_bit == 1) ? HIGH : LOW);
    }
}
