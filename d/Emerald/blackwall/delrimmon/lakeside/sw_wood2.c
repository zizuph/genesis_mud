/*
 *  /d/Emerald/blackwall/delrimmon/lakeshore/sw_wood2.c
 *
 *  Copyright (c) February 1998, by Cooper Sherry (Gorboth)
 *
 *  These woods lie on the southwesternmost slopes which ring the
 *  lake of Del Rimmon in the Blackwall Mountains of Emerald. They become
 *  denser as one travels northwest.
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
    set_side("southwest");
    set_show_area_desc();

    set_extraline("The slopes of the hillside amble northwest and"
                + " southeast along the shores of the lake, which are"
                + " visible here and there where there is a break in"
                + " the rows of trees.");

    add_item( ({"shores", "shores of the lake", "lakeshore",
                "lakeshores"}), BSN(
        "The shores of Del Rimmon peek now and again from between the"
      + " many tree trunks which cover this slope. An occasional lapping"
      + " of waves comes from the direction of the water, to the"
      + " northeast."));
    add_item( ({"rows", "row", "row of trees", "rows of trees"}), BSN(
        "The trees here grow tall and green, not nearly so thick as the"
      + " denser thickets which grow to the north and west, where the"
      + " slopes curve around the rim of the lake."));
    add_item( ({"break", "break in the rows of trees"}), BSN(
        "The occasional break in the rows of trees reveals the shoreline"
      + " of Del Rimmon, running northwest and southeast along the"
      + " edge of the water."));
    add_item( ({"thicket", "thickets",
                "dense thickets", "denser thickets"}), BSN(
        "The trees begin to grow thicker as the slopes run northwest"
      + " along the shores of the lake."));

    add_exit(DELRIMMON_DIR+"lakeside/sw_shore3","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_shore2","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff1", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_cliff2","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff3", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_wood2b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_wood3","northwest",check_sitting,1,1);

    set_no_exit_msg( ({ "northeast" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_tree_room */
