/*
 * /d/Emerald/blackwall/delrimmon/lakeside/w_wood4.c
 *
 * A stream flows through the forest here, making its way down to the
 * shores of Del Rimmon in the Blackwall Mountains of Emerald.
 *
 * Copyright (c) April 1998, by Cooper Sherry (Gorboth)
 *
 * Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room";
inherit "/d/Emerald/blackwall/delrimmon/stream.c";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 *  Prototypes
 */
public int     climb_embankment();

/*
 * Function name: create_tree_room
 * Description  : allows us to create room with presets to support
 *                the stream functions
 */
void
create_tree_room()
{
    Next_Stream = DELRIMMON_DIR + "lakeside/w_shore4";

    set_loc(2);
    set_side("west");
    set_show_area_desc();

    set_extraline("A stream winds through the forest here, flowing"
                + " down from the slopes to the northwest to empty"
                + " eastward to the shore of the lake.");

    add_stream_items();

    add_item( ({"shore", "lakeshore", "shore of the lake"}), BSN(
        "The shore to the east is somewhat visible here where a"
      + " narrow tract has been cut through the trees by the"
      + " channel of a flowing stream."));
    add_item( ({"tract", "narrow tract"}), BSN(
        "The trees separate where a narrow channel has been dug by"
      + " a stream flowing from the northwest."));
    add_item( ({"ground"}), BSN(
        "The undergrowth gives way along the ground here, where a"
      + " stream has dug a narrow channel which passes among the"
      + " tree trunks."));
    add_item( ({"root", "roots"}), BSN(
        "Roots from the nearby trees jut out into the narrow channel"
      + " which has been dug by the stream, winding their way into"
      + " the water."));
    add_item( ({"protrusion", "protrusions", "various protrusions"}),
    BSN("The channel in which the stream flows is cluttered here"
      + " and there by protrusions of one kind or another. The"
      + " water trickles and splashes freely among them."));

    add_cmd_item( ({"tree", "trees"}),
                  ({"climb"}), BSN(
        "None of the nearby trees have strong enough branches"
      + " so close to the ground that they might support your"
      + " weight."));

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    add_exit(DELRIMMON_DIR + "lakeside/w_wood5","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore5", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore4","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore3", "southeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5b", "northwest",
             climb_embankment, 10, 1);
} /* create_stream_room */

/*
 * Function name: describe_stream_hook
 * Description  : a redefinition to allow for a unique message to appear
 *                when players examine the stream.
 */
string
describe_stream_hook()
{
    return "The stream winds slightly as it dodges roots and the"
         + " trunks of trees, splashing here and there against"
         + " various protrusions. A narrow channel has been dug by the"
         + " water as it issues from the northwest, emptying down"
         + " the slope eastward to the lakeshore.";
} /* describe_stream_hook */

/*
 * Function name: climb_embankment
 * Description  : give the player a message about how rough the
 *                climb up the embankment is.
 * Arguments    : none
 * Returns      : 0
 */
public int
climb_embankment()
{
    WRITE("You trudge up the difficult slope, taking care not to"
        + " turn an ankle on the many loose stones in the dirt.");

    return 0;
} /* climb_embankment */


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
