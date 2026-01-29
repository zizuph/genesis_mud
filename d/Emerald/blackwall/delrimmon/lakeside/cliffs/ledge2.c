/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge2.c
 *
 *  A room near the southern end of a ledge extending along the western
 *  cliff faces of the hills surrounding Del Rimmon in Emerald.
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
    set_cliff_base(DELRIMMON_DIR + "lakeside/sw_cliff5");
    set_show_area_desc();

    set_extraline("A ledge runs along the face of the cliffs here,"
      + " high above the forested slopes below. As it runs northward,"
      + " the path seems to grow ever more perilous, requiring"
      + " great care for safe passage. To the south, the ledge winds"
      + " on a ways before halting at what appears to be an opening"
      + " of some kind in the cliff face.");

    add_item(({"slopes","forested slopes","below",
               "forested slopes below"}), BSN(
        "Far below this ledge, the slopes which surround Del Rimmon"
      + " run up against the base of these cliffs. Trees blanket"
      + " the slopes, ringing the lake in green foliage."));
    add_item(({"opening"}), BSN(
        "The opening in the cliff face to the south is too distant"
      + " to get a good look at from here. It is clearly more than"
      + " a simple alcove, however, as it is very dark within."));

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge3","northwest");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge1","southeast");

    set_no_exit_msg( ({ "north", "northeast", "east" }),
        "Peering at the steep drop, you decide not to step off the"
      + " ledge.\n");
    set_no_exit_msg( ({ "south", "southwest", "west" }),
        "You run up against the sheer faces of the cliffs in that"
      + " direction.\n");
} /* create_ledge */
