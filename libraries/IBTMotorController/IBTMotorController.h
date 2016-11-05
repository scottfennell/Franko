#ifndef IBTMotorController_h
#define IBTMotorController_h


#include "Arduino.h"


class IBTMotorController
{
protected:
    int _ena, _ena_1, _in1, _in2;
    int _currentSpeed;
    double _motorAConst;
public:
    IBTMotorController(int ena, ena_1, int in1, int in2, double motorAConst);
    void move(int speed);
    void move(int speed, int minAbsSpeed);
    void stopMoving();
};


#endif
