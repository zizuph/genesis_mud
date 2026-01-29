/*
 * catacomb_3.c
 *
 * A room in the catacombs below Castle Chimera.
 *
 * Coded by Khail, June 4/96
 */

#pragma strict_types

#include "defs.h"

inherit CATBASE;

public void
create_room()
{
    create_catacomb();

    set_short("in the catacombs beneath " + CASTLE_NAME);
    set_long("You are in what appear to be catacombs of some sort beneath " +
        CASTLE_NAME + ". Dark and gloomy, the passage is square-shaped, " +
        "and apparently hewn from solid stone, and smoothly finished. " +
        "Oddly enough, the only evidence of " +
        "age here is the thick dust coating everything, and the rust " +
        "which has formed on the sconces that are embedded in the walls. " +
        "At the east end of the tunnel, a narrow stone stairway " +
        "spirals upwards through the stone and darkness. " +
        "While the stairway to the east is fairly dark, " +
        "you can see a glimmer of light towards the west, and you think " +
        "you can hear the trickle of running water from that " +
        "direction.\n\n");

    add_item(({"walls"}),
        "The walls are well made, and the room must be very deep indeed, " +
        "as the age of the castle would surely mean the walls would have " +
        "eroded to at least some extent.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "catacomb_5", "up");
    add_exit(RUIN + "catacomb_hub", "west");
 }
