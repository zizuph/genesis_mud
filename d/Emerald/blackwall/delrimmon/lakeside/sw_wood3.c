/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood3.c
 *
 *  Here the slopes along the shores of Del Rimmon wind northwest and
 *  southeast, marred only occasionally by thorny brambles.
 *
 *  Copyright (c) February 1998, by Gorboth (Cooper Sherry)
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

    set_extraline("The tree-clad slopes wind their way along the"
                + " lake here, interrupted every so often by"
                + " dense thickets of brambles.");

    add_item( ({"tree-clad slopes"}), BSN(
        "The slopes trace the edge of the lake here at this west-"
      + "southwest point from the center of the lake."));
    add_item( ({"thicket", "thickets", "dense thicket", "brambles",
                "thicket of brambles", "thickets of brambles",
                "dense thickets of brambles",
                "dense thicket of brambles",}), BSN(
        "In various places, brambles wind their way along the"
      + " mossy slopes here, choking the ground and tree trunks."));
    add_item( ({"ground"}), BSN(
        "The ground is grassy and covered with patchy mosses and"
      + " undergrowth amongst the many tree trunks. In places,"
      + " thickets of brambles choke the way."));
    add_item( ({"mossy slope", "mossy slopes"}), BSN(
        "The slopes here run gradually along the edge of the lake"
      + " which lies to the east. The ground is green with moss in"
      + " many places, where the thickets have not run too thick"
      + " with brambles."));
    add_item( ({"vegetation", "bits of vegetation",
                "sunken bits of vegetation",}), BSN(
        "Beneath the brambles, vegetation has found a quiet place to"
      + " sit and rot."));
    add_item( ({"brown moss"}), BSN(
        "The moss which can be found beneath the thickets of brambles"
      + " is brown and moist, as if the lack of sunlight and abundance"
      + " of decay has tainted its pigment."));

    add_cmd_item( ({"brambles", "thicket", "thickets",
                    "dense thicket", "dense thickets",
                    "dense thicket of brambles",
                    "dense thickets of brambles,"}),
                  ({"search", "dig"}), BSN(
        "The brambles are damp and soggy, bending wetly to the"
      + " touch. Aside from brown moss and various sunken bits"
      + " of vegetation, there is nothing of interest to be found."));

    add_exit(DELRIMMON_DIR+"lakeside/sw_shore3","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_wood2","southeast",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_wood2b","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff4", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_wood3b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/w_wood1","northwest",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/w_shore1","north",check_sitting,1,1);

    set_no_exit_msg( ({ "northeast" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");

    add_view();
} /* create_tree_room */
