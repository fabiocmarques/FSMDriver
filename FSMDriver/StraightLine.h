#ifndef FSMDRIVER_STATE_STRAIGHTLINE_H
#define FSMDRIVER_STATE_STRAIGHTLINE_H

#include "FSM.h"

/******************************************************************************/
int START_GEAR = 1;
int LOW_GEAR_LIMIT = 4;

int LOW_RPM = 1500;
int AVERAGE_RPM = 4000;
int HIGH_RPM = 9500;
/******************************************************************************/

class FSMDriver;

class StraightLine : public DrivingState<FSMDriver> {
public:
    static StraightLine *instance() {
        static StraightLine instance;
        return &instance;
    }

private:
    StraightLine() {}
    StraightLine(StraightLine const &);
    void operator=(StraightLine const&);

public:
    ~StraightLine(){}

    void enter(FSMDriver *driver) {
        //cout << "Enter StraightLine" << endl;
    }

    void exit(FSMDriver *driver) {
        //cout << "Exit StraightLine" << endl;
    }

    virtual CarControl drive(FSMDriver *fsmdriver, CarState &cs) {
        const float accel = 1, brake = 0, clutch = 0;
        const int focus = 0, meta = 0;
        float steer = cs.getAngle();

        return CarControl(accel, brake, getGear(cs), steer, clutch, focus, meta);
    }

private:
    static inline bool runningOnLow(int rpm) {
        return (rpm < LOW_RPM);
    }
    static inline bool runningUnderAverage(int rpm) {
        return (rpm <= AVERAGE_RPM);
    }
    static inline bool runningOnHigh(int rpm) {
        return (rpm > HIGH_RPM);
    }
    static inline bool isLowGear(int gear) {
        return (gear > START_GEAR && gear < LOW_GEAR_LIMIT);
    }
    static inline bool isHighGear(int gear) {
        return (gear >= LOW_GEAR_LIMIT);
    }
    static bool shouldDecreaseGear(int currentGear, int rpm) {
        if(isLowGear(currentGear) && runningOnLow(rpm)) return true;
        if(isHighGear(currentGear) && runningUnderAverage(rpm)) return true;
        return false;
    }
    static inline bool shouldIncreaseGear(int currentGear, int rpm) {
        return runningOnHigh(rpm);
    }
    float getBrake(CarState &cs) {
        return (cs.getSpeedX() < 0 ? 1:0);
    }

public:
    static int getGear(CarState &cs) {
        int gear = cs.getGear();
        if(gear <= 0) return START_GEAR;

        int rpm = cs.getRpm();

        if(shouldIncreaseGear(gear, rpm)) ++gear;
        else if(shouldDecreaseGear(gear, rpm)) --gear;

        return gear;
    }
};

#endif // FSMDRIVER_STATE_STRAIGHTLINE_H
