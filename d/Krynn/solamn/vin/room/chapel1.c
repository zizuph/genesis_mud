/*
 * File name:       /d/Krynn/solamn/vin/room/chapel1.c
 * Description:     The first (most eastern) room in the Vingaard
 *                  chapel.
 *
 * Copyright (c):   Sep. 1999 by Daniel W. Mathiasen (Boron)
 *
 * Revision history:
 * When     -   Who     -   What
 * --------------------------------
 *
 */
#include "../knight/guild.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

public void
create_vin_room()
{
    set_short("Chapel of the Dead");
    set_long("You stand in a great hall below Vingaard Keep. "
           + "The walls are made of great stone blocks, and the "
           + "floor is covered by flagstone. The hall "
           + "is about sixty feet wide and at least three times "
           + "as long. At one end there is a huge doorway leading "
           + "out and up a few stairs. At the other end there is "
           + "an altar carved in wood. There is a deep rose red "
           + "carpet covering the flagstone from the doorway down "
           + "to the altar. Along the walls stone tombs are placed, "
           + "above each tomb a burning torch is fitted into an iron "
           + "sconce.\n");

    add_item(({"wall","walls", "great stone blocks", "stone blocks", "blocks"}),
                    "The walls are constructed of great granite stone "
                  + "blocks. They seem perfectly plain and smooth.\n");

    add_item(({"flagstone","floor","flagstones", "carpet", "red carpet"}),
                    "The flagstone floor is made of black shiny marble. It covers "
                  + "the floor from wall to wall. Between the rows of tombs, "
                  + "a deep rose red carpet runs west down to the wooden "
                  + "altar.\n");

    add_item(({"door", "doorway", "stairs"}), 
                    "The huge doorway seems neatly cut in the great stone "
                  + "blocks. The stairway leads up into Vingaard Keep.\n");

    add_item(({"altar","wooden altar"}), 
                    "In the other end of the great hall you notice an altar, "
                  + "carved in ebony. There seem to be some patterns in the "
                  + "altar, but it is too far to see detailed.\n");

    add_item(({"tombs", "tomb", "coffin", "coffins"}),
                    "The stone coffins of the dead line the walls of the "
                  + "great hall. At the feet of each coffin is an iron plaque "
                  + "giving the name, the title, the family and the date of the "
                  + "burial of the dead Knight. Above each coffin, fitted "
                  + "into an iron sconce is a burning torch, casting a dim "
                  + "vivid light throughout the hall.\n");

    add_item(({"torches", "torch", "iron sconces", "sconces", "sconce"}), 
                    "The flames of the torches in the iron sconces, seem to have "
                  + "darkened the walls behind the flames with dark sod. The "
                  + "flames cast a vivid dim light over the tombs and through the "
                  + "hall.\n");

    add_item(({"hall", "great hall"}),
                    "This is the Chapel of the Dead.\n");

    seteuid(getuid(TO));


}
