#include <iostream>
#include <string>
#include <sstream>

enum power {
    powerSupply,
    sockets,
    lightInside,
    lightOutside,
    heating,
    waterHeating,
    conditioner
};

void stringToBool(std::string &text, bool &status) {
    if (text == "yes" or text == "on")
        status = true;
    else status = false;
}

void waterHeatingSwitch(int& state, float& temperatureOutside) {
    if (temperatureOutside < 0 and !(state & waterHeating)) {
        state |= waterHeating;
        std::cout << "Water heating system: ON"<<std::endl;
    } else if (temperatureOutside > 5 and (state & waterHeating)) {
        state &= ~waterHeating;
        std::cout << "Water heating system: OFF"<<std::endl;
    }
}

void lightOutsideSwitch(int& state, int& hour, bool& movingOutsideStatus ) {
    if ((hour > 16 or hour < 5) and movingOutsideStatus==1 and !(state & lightOutside)) {
        state |= lightOutside;
        std::cout << "Light outside: ON"<<std::endl;
    } else if (((hour <= 16 and hour >= 5) or movingOutsideStatus==0)  and (state & lightOutside)) {
        state &= ~lightOutside;
        std::cout << "Light outside: OFF"<<std::endl;
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


    int state = 0;

    for (int day = 1; day < 2; day++) {
        hour = 0;
        for (; hour < maxHour; hour++) {
            std::cout << "Day #" << day << " " << hour << ":00" << std::endl;
            std::cout
                    << "Enter temperature inside and outside, moving outside status(yes/no), light on inside status(on/off): "
                    << std::endl;
            std::cin >> temperatureInside >> temperatureOutside >> movingOutsideStatusText >> lightOnInsideStatusText;
            stringToBool(movingOutsideStatusText, movingOutsideStatus);
            stringToBool(lightOnInsideStatusText, lightOnInsideStatus);
            waterHeatingSwitch(state,temperatureOutside);
            lightOutsideSwitch(state, hour,movingOutsideStatus);
        }
    }
}
