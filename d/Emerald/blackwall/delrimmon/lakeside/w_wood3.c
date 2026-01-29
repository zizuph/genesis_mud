/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood3.c
 *
 *  This stretch of woods lies due west from Del Rimmon in the Blackwall
 *  Mountains. Just to the south lies a bit of a clearing.
 *
 *  Copyright (c) April 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */

#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_tree_room
 * Destcription : lets us create the room
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("west");

    set_extraline("These woods lie directly west of the center of the"
                + " lake of Del Rimmon, running gradually along the"
                + " slopes which travel along the shore to the east."
                + " A bit to the south, a clearing of sorts seems to"
                + " open up from between the trees.");

    add_item( ({"wood", "woods"}), BSN(
        "Trees are all about, covering the slopes which run to the north"
      + " and south. The branches above create the effect of a high"
      + " ceiling which covers the area."));
    add_item( ({"ceiling", "high ceiling"}), BSN(
        "The cover of the branches seems somehow comforting, as if it"
      + " might protect those who walk beneath."));
    add_item( ({"shore", "shores"}), BSN(
        "The shore of the lake is not visible from here, but glimpses"
      + " of the water are occasionally available through a gap in"
      + " the tree trunks to the east."));
    add_item( ({ "gap", "gaps", "gap in the tree trunks" }),
        BSN("An occasional gap in the tree trunks to the east provides"
          + " a brief glimpse of the water of the lake. You cannot see"
          + " much in the way of specifics from here."));
    add_item( ({"center", "center of the lake"}), BSN(
        "The lake itself is not visible, yet the impression is clear"
      + " that this stretch of the woods lies due west from its"
      + " center."));
    add_item( ({"clearing"}), BSN(
        "South of here, the trees fall away somewhat, opening onto"
      + " what appears to be a clearing in the woods."));

    add_cmd_item( ({"clearing"}),
                  ({"search", "dig"}), BSN(
        "The clearing is a ways yet to the south. You will need to"
      + " travel in that direction first."));

    add_exit(DELRIMMON_DIR + "lakeside/w_wood4","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore4", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore3","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore2", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b", "northwest",
             check_sitting,1,1);
} /* create_tree_room */
