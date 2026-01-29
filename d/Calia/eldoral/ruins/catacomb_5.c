#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("on a narrow stairway beneath " + CASTLE_NAME);
    set_long("You are upon a narrow stairway that spirals upwards " +
        "through solid rock. It's quite dusty, possibly the occasional " +
        "breeze blows in dust from the ruins above somewhere. While all " +
        "above seems quiet, you believe you can make out a hint of " +
        "noise from somewhere below, almost like running water. Here " +
        "and there on the outer wall of the stairway, a rusty iron sconce " +
        "bears a reminder that at one time, this ruin was actually lived " +
        "in.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling here roughly mirrors the steps. It's formed by " +
        "long slabs of stone that reach across the walls, and follow " +
        "the curve of the stairway upwards and downwards.\n");
    add_item(({"walls"}),
        "The walls are cut from the surrounding stone, smoothly " +
        "finished to provide a graceful curve to the walls as they " +
        "wrap around the spiral stairway.\n");
    add_item(({"floor", "ground", "steps"}),
        "The floor is made up of long slabs of stone that have been " +
        "fitted against the ground in some means, rather than being " +
        "cut from the surrounding stone like the walls were.\n");
    add_item(({"sconce", "iron sconce"}),
        "The sconces are simple iron rings, now coated in rust, " +
        "which are firmly embedded into the stone of the walls.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "build6", "up");
    add_exit(RUIN + "catacomb_3", "down");
}

