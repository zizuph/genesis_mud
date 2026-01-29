/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_wood3.c
 *
 *  This is the most eastern northerly patch of forest which grows
 *  on the west banks of Del Rimmon in the Blackwall Mountains of Gongor.
 *  The trees grow rather thinly here.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("northwest");
    set_show_area_desc();

    set_extraline("The trees which make up this bit of forest seem"
                + " rather thin, and spaced from one another. To the"
                + " west, the foliage appears to grow much more"
                + " densely.");

    add_item( ({"foliage", "foliage to the west"}), BSN(
        "The forest appears to grow more densely to the west, where"
      + " the shadows appear darker and more thickly clustered."));
    add_item( ({"shadow", "shadows"}), BSN(
        "Shadows are deeper to the west, where the trees seem to"
      + " grow more densely."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff5","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff6", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff7","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore3", "southeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore2","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff4", "northwest",
             check_sitting, 1, 1);
} /* create_tree_room */
