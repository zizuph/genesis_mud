/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood5b.c
 *
 *  A stream runs through the woods here, where a steep embankment falls
 *  to the south and east. These are the western slopes which surround
 *  Del Rimmon in the Blackwall Mountains. A waterfall is just to the
 *  north.
 *
 *  Copyright (c) July 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room";
inherit "/d/Emerald/blackwall/delrimmon/stream.c";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with presets to support
 *                the tree functions
 */
void
create_tree_room()
{
    Next_Stream = DELRIMMON_DIR + "lakeside/w_wood4";

    set_loc(2);
    set_side("west");
    set_show_area_desc();

    set_extraline("Filtering through a gap in the trees to the north,"
                + " a stream winds its way along the forest floor here,"
                + " emptying down the hillside to the southeast over"
                + " the brink of a steep embankment.");

    add_stream_items();

    add_item( ({"gap", "gap in the trees"}), BSN(
        "A few paces to the north, the trees part somewhat where"
      + " a stream flows through this portion of the woods along"
      + " the hillside. What appears to be a small waterfall is"
      + " visible through the trees."));
    add_item( ({"waterfall", "small waterfall"}), BSN(
        "The waterfall flows down the cliffs to the north, which"
      + " are somewhat visible between a gap in the trees here."));
    add_item( ({"cliffs to the north", "northern cliffs"}), BSN(
        "The cliffs to the north are visible peering between a gap"
      + " in the trees where a stream has cut a path. It appears"
      + " as if a waterfall flows there, but from this distance,"
      + " little detail can be clearly seen."));
    add_item( ({"base", "base of the slope"}), BSN(
        "The base of the slope would be quite a distance to the"
      + " east, where the lake of Del Rimmon meets with the hillside"
      + " to form a long crescent shoreline."));
    add_item( ({"shoreline"}), BSN(
        "The shoreline is not visible through the trees."));
    add_item( ({"path"}), BSN(
        "A narrow channel has been carved by the stream, parting"
      + " the trees to the north, and the edge of a steep"
      + " embankment to the southeast."));
    add_item( ({"floor", "forest floor", "ground"}), BSN(
        "The ground is rather level here, except where a narrow"
      + " channel has been carved by a swiftly flowing stream."));
    add_item( ({"brink", "brink of a steep embankment"}), BSN(
        "The brink of the embankment appears rather suddenly to the"
      + " east and south. It is cloven somewhat by the stream,"
      + " which flows over its edge directly to the southeast."));
    add_item( ({"edge"}), BSN(
        "The edge of the brink is cloven by the stream which has"
      + " eroded away the ground."));
    add_item( ({"embankment", "steep embankment"}), BSN(
        "The embankment slopes steeply downhill to the south and"
      + " east, where it disappears among the trees into the"
      + " forested hillsides below."));
    add_item( ({"forested hillsides"}), BSN(
        "The hillsides appear quite lovely and serene here in"
      + " the Blackwall Mountains."));

    add_cmd_item( ({"waterfall", "northern cliffs"}),
                  ({"search", "climb"}), BSN(
        "The northern cliffs are still quite a distance to the"
      + " north, through a gap in the trees."));

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    add_exit(DELRIMMON_DIR + "lakeside/nw_cliff1","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1b","northeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5","east",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4","southeast",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b","south",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff4","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff5","west",0,1,1);

    set_no_exit_msg( ({ "northwest" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");
} /* create_stream_room */

/*
 * Function name: describe_stream_hook
 * Description  : a redefinition to allow for a unique message to appear
 *                when players examine the stream.
 */
string
describe_stream_hook()
{
    return "The stream issues from the north, and runs rapidly"
         + " along the fairly level ground here before tumbling"
         + " down the embankment on its journey"
         + " towards the base of the slope.";
} /* describe_stream_hook */


/*
 * Function name:        init
 * Description  :        add soma actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_drink, "drink");
} /* init */
