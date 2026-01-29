/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood1b.c
 *
 *  The forest continues to ring the lake here, west southwest from
 *  the center of Del Rimmon in the Blackwall Mountains of Emerald.
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
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
    set_side("west");
    set_show_area_desc();

    set_extraline("The slope of the hillside grows steeper to the"
                + " west, where the stone faces of towering cliffs"
                + " are visible between gaps in the trees.");

    add_item( ({"face", "faces", "stone face", "stone faces",
                "stone faces of towering cliffs",
                "towering cliff", "towering cliffs"}), BSN(
        "To the west, the tall and sheer faces of the cliffs which"
      + " surround this region can be glimpsed now and again"
      + " peering between the gaps in the tree trunks.") );
    add_item( ({"gap", "gaps", "gaps in the tree trunks"}), BSN(
        "The towering cliffs of the Blackwall Mountains are visible between"
      + " gaps in the trees to the west.") );

    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood1","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood3b", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff5","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff1","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff2", "northwest",
             check_sitting,1,1);

    set_no_exit_msg( ({ "southwest" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_tree_room */
