/*
 *  room_funcs.c
 *
 *  Various functions for Anghoth club rooms
 *
 *  Alto, 13 June 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <options.h>

/* Global variables */


/* Prototypes */

public void        anghoth_add_items();

void
anghoth_add_items()
{
    add_item(({"floor", "stone floor", "ground"}), "The floor here "
        + "is made from solid stone. In most places it is worn smooth "
        + "by the passage of many booted feet over thousands of years.\n");
    add_item(({"stone"}), "Many snaga bled to quarry this stone.\n");
    add_item(({"wall", "walls"}), 
        "The walls are made from solid stone and are very cold to the "
        + "touch. There is great strength but little comfort in this "
        + "room.\n");
    add_item(({"ceiling"}), "The ceiling is high and difficult to "
        + "discern in the dim light. You can see that, like the rest of "
        + "the room, it is made from solid stone.\n");
}
