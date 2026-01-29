/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge1.c
 *
 *  This is the southernmost point on a ledge which runs a large
 *  portion of the length of the western ridge of cliffs in the
 *  Blackwall Mountains.
 *
 *  Copyright (c) July 1997, Cooper Sherry (Gorboth)
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
    set_cliff_base(DELRIMMON_DIR + "lakeside/sw_cliff4");

    set_extraline("A long and narrow ledge winds along the face of"
      + " the cliff here in a general north-south direction. It"
      + " is likely that traversing such terrain would require"
      + " considerable balance. To the south, a small tunnel opening"
      + " leads down into the interior of the cliffside. To the"
      + " east, the lake of Del Rimmon is clearly visible in"
      + " its shimmering glory.");

    add_item(({"tunnel","tunnel opening","small tunnel",
               "small tunnel opening","opening"}), BSN(
        "The tunnel opening is almost perfectly rectangular, with"
      + " slightly rounded edges. There is no question that it was"
      + " hewn from the rock by skilled hands, yet the weathered"
      + " look of the surfaces makes it difficult to tell how many"
      + " centuries ago it was created. It leads into darkness to"
      + " the south."));
    add_item(({"rock","rock face","cliffside"}), BSN(
        "The rock face of the cliffs here is interrupted by a tunnel"
      + " opening which has been carved into the cliffs to the"
      + " south."));
    add_item(({"edge","edges","surface","surfaces"}), BSN(
        "There are no marks in the surface of the stone where the"
      + " tunnel has been dug into the cliff. Clearly, there was"
      + " master craftsmanship at work in this endeavor."));


    add_exit(DELRIMMON_DIR + "lakeside/cliffs/tunnel4","south");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge2", "northwest");

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast" }),
        "You peer at the steep drop next to the ledge, and decide"
      + " that it is probably best to stay on the path.\n");
    set_no_exit_msg( ({ "southwest", "west" }),
        "The steep walls of the cliffs rise to block your passage"
      + " in that direction.\n");
} /* create_ledge */
