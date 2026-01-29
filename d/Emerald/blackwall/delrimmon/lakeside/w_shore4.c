/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_shore4.c
 *
 *  This beach is slightly north of the westernmost point of the
 *  lake of Del Rimmon in Emerald. A stream runs out of the woods
 *  to meet with the lake here.
 *
 *  Copyright (c) September 1997 by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 *  Added fishing     : August 2021 (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeshore";
inherit "/d/Emerald/blackwall/delrimmon/stream.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_lakeshore_room
 * Description  : allows us to create the room with area presets
 */
public void
create_lakeshore()
{
    set_loc(1);
    set_side("west");

    set_extraline("A stream has dug a narrow channel in the ground"
                + " here, as it flows east out of the woods along"
                + " the hillsides to meet with the waters of the" 
                + " lake.");

    add_stream_items();

    add_item( ({"ground"}), BSN(
        "The level surface of the ground has been broken here by"
      + " a stream which flows out of the trees to the west to"
      + " meet with the waters of the lake."));
    add_item( ({"wood", "woods"}), BSN(
        "To the west, trees cover the sloping hillside which"
      + " ambles gradually towards the feet of the distant cliffs."
      + " A stream flows quietly from between the trees, and passes"
      + " through a narrow channel here on its way to join with the"
      + " waters of the lake."));

    add_exit(DELRIMMON_DIR + "lakeside/w_shore5","north");
    add_exit(DELRIMMON_DIR + "lakeside/w_shore3","south");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5","northwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
        "Going that way would require a lot of swimming.\n");
} /* create_stream_room */

/*
 * Function name: describe_stream_hook
 * Description  : we redefine this hook to change the look of the
 *                stream to something unique for this room
 * Returns      : string - special desc for this room's stream
 */
string
describe_stream_hook()
{
    return "The water of the stream sparkles as it quietly trickles"
         + " through the pebbles to meet with Del Rimmon. It runs"
         + " from the forested slopes to the west, perhaps fed by"
         + " some unknown source in the cliffs above.";
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
