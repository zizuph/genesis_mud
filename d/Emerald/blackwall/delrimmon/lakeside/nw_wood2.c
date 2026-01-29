/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_wood2.c
 *
 *  A cleft marks the meeting place of two landmasses on this slope of
 *  the northwestern hills which surround Del Rimmon in the Blackwall
 *  Mountains.
 *
 *  Copyright (c) August 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
void    create_tree_room();

/*
 * Function name:    create_tree_room
 * Description  :    allows us to create the room with area presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("northwest");
    set_show_area_desc();

    set_extraline("A cleft in the slope of the hillside winds its"
                + " way down to the shore of the lake to the south,"
                + " creating somewhat of an aisle amid the many"
                + " tree trunks.");

    add_item( ({"cleft", "cleft in the slope",
                "cleft in the slope of the hillside"}), BSN(
        "The cleft appears not to be the product of any water"
      + " erosion, but rather the meeting place for two bits of"
      + " land which butt up against one another."));
    add_item( ({"bits of land", "two bits of land"}), BSN(
        "The two slopes which come together to form the cleft here"
      + " run at similar pitch, but travel at different angles"
      + " in comparison to the shore of the lake."));
    add_item( ({"shore of the lake"}), BSN(
        "The shore of the lake can be glimpsed now and again"
      + " through the trunks of trees to the south."));
    add_item( ({"slope of the hillside"}), BSN(
        "The slope of the hillside is marked by a cleft which"
      + " runs down to the lakeshore here."));
    add_item( ({"aisle"}), BSN(
        "The trees along this hillside do not grow in the cleft"
      + " which runs down to the lake, giving the effect of an"
      + " aisle flowing between the trunks."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3b","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood3", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore2","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore1","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff3", "northwest",
             check_sitting, 1, 1);

    set_no_exit_msg( ({ "southeast" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_tree_room */
