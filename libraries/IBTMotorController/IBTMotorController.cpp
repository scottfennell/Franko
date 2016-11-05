#include "IBTMotorController.h"
#include "Arduino.h"


IBTMotorController::IBTMotorController(int ena, int ena_1, int in1, int in2, double motorAConst)
{
    _motorAConst = motorAConst;

	_ena = ena;
  _ena_1 = ena_1;
	_in1 = in1;
	_in2 = in2;


	pinMode(_ena, OUTPUT);
  pinMode(_ena_1, OUTPUT);
	pinMode(_in1, OUTPUT);
	pinMode(_in2, OUTPUT);

}

void IBTMotorController::move(int speed, int minAbsSpeed)
{
    int direction = 1;

    if (speed < 0)
    {
        direction = -1;

        speed = min(speed, -1*minAbsSpeed);
        speed = max(speed, -255);
    }
    else
    {
        speed = max(speed, minAbsSpeed);
        speed = min(speed, 255);
    }

    if (speed == _currentSpeed) return;

    int realSpeed = max(minAbsSpeed, abs(speed));

    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in2, speed > 0 ? LOW : HIGH);

    if (speed > 0) {
      analogWrite(_ena, realSpeed * _motorAConst);
      analogWrite(_ena_1, 0);
    } else {
      analogWrite(_ena, 0);
      analogWrite(_ena_1, realSpeed * _motorAConst);
    }
    _currentSpeed = direction * realSpeed;
}


void IBTMotorController::move(int speed)
{
    if (speed == _currentSpeed) return;

    if (speed > 255) speed = 255;
    else if (speed < -255) speed = -255;

    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in2, speed > 0 ? LOW : HIGH);
    if (speed > 0) {
      analogWrite(_ena, abs(speed) * _motorAConst);
      analogWrite(_ena_1, 0);
    } else {
      analogWrite(_ena, 0);
      analogWrite(_ena_1, abs(speed) * _motorAConst);
    }

    _currentSpeed = speed;
}

void IBTMotorController::stopMoving()
{
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_ena, HIGH);
    digitalWrite(_ena_1, HIGH);

    _currentSpeed = 0;
}
