#include <iostream>
#include <string>
#include <sstream>

enum power {
    powerSupply = 1,
    sockets = 2,
    lightInside = 4,
    lightOutside = 8,
    heating = 16,
    waterHeating = 32,
    conditioner = 64
};

void stringToBool(std::string &text, bool &status) {
    if (text == "yes" or text == "on")
        status = true;
    else status = false;
}

void waterHeatingSwitch(int &state, float &temperatureOutside) {
    if (temperatureOutside < 0 and !(state & waterHeating)) {
        state |= waterHeating;
        std::cout << "Water heating system: ON" << std::endl;
    } else if (temperatureOutside > 5 and (state & waterHeating)) {
        state &= ~waterHeating;
        std::cout << "Water heating system: OFF" << std::endl;
    }
}

void lightOutsideSwitch(int &state, int &hour, bool &movingOutsideStatus) {
    if ((hour > 16 or hour < 5) and movingOutsideStatus == 1 and !(state & lightOutside)) {
        state |= lightOutside;
        std::cout << "Light outside: ON" << std::endl;
    } else if (((hour <= 16 or hour >= 5) and movingOutsideStatus == 0) and (state & lightOutside)) {
        state &= ~lightOutside;
        std::cout << "Light outside: OFF" << std::endl;
    }
}

void heatingSwitch(int &state, float &temperatureInside) {
    if (temperatureInside <= 22 and !(state & heating)) {
        state |= heating;
        std::cout << "Heating: ON" << std::endl;
    } else if (temperatureInside >= 25 and (state & heating)) {
        state &= ~heating;
        std::cout << "Heating: OFF" << std::endl;
    }
}

void conditionerSwitch(int &state, float &temperatureInside) {
    if (temperatureInside >= 30 and !(state & conditioner)) {
        state |= conditioner;
        std::cout << "Conditioner: ON" << std::endl;
    } else if (temperatureInside <= 25 and (state & conditioner)) {
        state &= ~conditioner;
        std::cout << "Conditioner: OFF" << std::endl;
    }
}

void lightTemperatureInsideSwitch(bool &lightOnInsideStatus, int &hour, int &lightTemperature) {
    if (lightOnInsideStatus == 1 and (hour >= 15 and hour <= 20)) {
        std::cout << "Light Temperature Inside: " << lightTemperature << " K" << std::endl;
        lightTemperature -= 460;
    } else if (lightOnInsideStatus == 0 and (hour >= 16 and hour <= 20)) {
        lightTemperature -= 460;
    }
}

int main() {
    int hour;
    int maxHour = 24;

    float temperatureInside = 0, temperatureOutside = 0;

    bool movingOutsideStatus;
    std::string movingOutsideStatusText;

    bool lightOnInsideStatus;
    std::string lightOnInsideStatusText;

    int lightTemperature;

    int state = 0;

    for (int day = 1; day < 2; day++) {
        hour = 0;
        lightTemperature = 5000;
        for (; hour < maxHour; hour++) {
            std::cout << "Day #" << day << " " << hour << ":00" << std::endl;
            std::cout
                    << "Enter temperature inside and outside, moving outside status(yes/no), light on inside status(on/off): "
                    << std::endl;
            std::cin >> temperatureInside >> temperatureOutside >> movingOutsideStatusText >> lightOnInsideStatusText;
            stringToBool(movingOutsideStatusText, movingOutsideStatus);
            stringToBool(lightOnInsideStatusText, lightOnInsideStatus);
            waterHeatingSwitch(state, temperatureOutside);
            lightOutsideSwitch(state, hour, movingOutsideStatus);
            heatingSwitch(state, temperatureInside);
            conditionerSwitch(state, temperatureInside);
            lightTemperatureInsideSwitch(lightOnInsideStatus, hour, lightTemperature);
        }
    }
}
