/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge4.c
 *
 *  The ledge along the west slopes of the Blackwall Mountains is now
 *  winding here in a northwesterly direction towards its western
 *  apex.
 *
 *  Copyright (c) August 1997, by Cooper Sherry (Gorboth)
 * 
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_ledge
 * Description  : allows us to create the room with area presets
 */
void
create_ledge()
{
    set_cliff_base(DELRIMMON_DIR + "lakeside/w_cliff2");
    set_show_area_desc();

    set_extraline("The narrow ledge continues along the face of the"
      + " cliffs here, curving slowly north and west along the"
      + " steep slopes. The view of the lake to the east remains"
      + " impressive.");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge5","northwest");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge3","south");

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast" }),
        "A sheer drop from the ledge is all that lies in that"
      + " direction.\n");
    set_no_exit_msg( ({ "southwest", "west" }),
        "Sheer cliff faces block your movement in that direction.\n");
} /* create_ledge */
