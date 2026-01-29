#ifndef _KABAL_LIFT_
#define _KABAL_LIFT_

#include "/d/Kalad/sys/paths.h"

// Lift status
#define LIFT_READY	0
#define MOVING_UP       1
#define MOVING_DOWN     2
#define LIFT_RESTING	3

// Lift locations
#define AT_BOTTOM	0
#define AT_TOP		1

// Lift rooms to connect to
#define TOP_ROOM        (CENTRAL + "lift_room")
#define BOTTOM_ROOM     (PORT + "s8")

// The lift room
#define LIFT            (PORT + "lift")

#define LIFT_MSGS ({ \
        "The lift lurches slightly in mid-transit.\n", \
        "The lift swings about as it's buffeted by winds.\n", \
        "The lift abruptly drops a few feet before it lunges "+ \
        "to a sudden stop then begins moving once more.\n", \
        "The ropes supporting the lift groan a bit under the stress.\n", \
        "An updraft causes the lift to tilt precariously for a moment.\n", \
        })

#endif _KABAL_LIFT_
