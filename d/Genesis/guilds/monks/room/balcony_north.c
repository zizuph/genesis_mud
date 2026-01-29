/*
 * File:    balcony_north
 * Creator: Cirion, 1998.06.14
 * Purpose: northern balcony of the monks guild hall
 */
#pragma strict_types

#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("northern balcony");
    set_long("A fresh spring breeze blows across this wide "
        + "stone balcony which overlooks the green grass "
        + "that covers the front entrance of the monastery. "
        + "A leaded glass door leads into the northern hall "
        + "to the south."
        + living_view("lawn_ne", " Standing on the lawn below "
        + "you, you see ", ".", "")
        + "\n");
    add_item(({"lawn","grass","down"}),
        "The lawn stretching down below is fertile and "
        + "well-kept. The wind washes over it, causing the "
        + "blades of grass to undualte in perfect harmony.\n");
    add_item(({"door","doors","lead","glass"}),
        "The leaded glass doors open to the south into the "
        + "upper hall of the monastery.\n");

    add_cmd_item(({"wind","breeze","air"}), ({"feel","touch"}),
        "The spring breeze feels cool and refreshing on "
        + "your face.\n"
        + VBFC_SAY("breathes in the fresh spring air.\n"));


    // where, command
    add_exit("hall_upper_north", "south");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("south", "A fresh spring breeze meets you "
        + "as you walk out onto the balcony.\n");
}

