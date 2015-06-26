/**  @file: FSMDriver5.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */


#ifndef UNB_FSMDRIVER_FSMDRIVER5_H
#define UNB_FSMDRIVER_FSMDRIVER5_H

#include "FSMDriver.h"
#include "ApproachingCurve.h"
#include "StraightLine.h"
#include "Curve.h"
#include "OutOfTrack.h"
#include "Stuck.h"

#include <vector>
#include <bitset>

/** A controller with a 5-state FSM.
 *
 * @todo describe class.
 * @todo document attributes, fix attribute names (no caps-only).
 * @todo document methods */
class FSMDriver5 : public FSMDriver {
private:
    StraightLine straight_line;
    ApproachingCurve approaching_curve;
    Curve curve;
    OutOfTrack out_of_track;
    Stuck stuck;

    int segment_id;

    int max_straight_line_var;
    int min_straight_line_var;
    int max_approaching_curve_var;
    int min_approaching_curve_var;


public:
    virtual void onShutdown();
    virtual void onRestart();

    /** Initialization of the desired angles for the range finders. */
    virtual void init(float *angles);

    FSMDriver5();
    virtual ~FSMDriver5();

    /** Transitions between states (if appropriate).
     * @todo fix documentation. */
    void transition(CarState &);
};

#endif // UNB_FSMDRIVER_FSMDRIVER5_H
