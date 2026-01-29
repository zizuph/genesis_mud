/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_shore5.c
 *
 *  Here the shores along the western edge of Del Rimmon in Emerald
 *  turn slightly north northeast as one travels in that direction.
 *
 *  Copyright (c) September 1997 by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 *  Added fishing     : August 2021 (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeshore.c";

#include <ss_types.h>     // for SS_TRACKING
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Function name: create_lakeshore
 * Description  : allows us to create the room with area presets
 */
void
create_lakeshore()
{
    set_loc(1);
    set_side("west");
    set_show_area_desc();

    set_extraline("The lake shore curves slightly to the northeast"
                + " here, making its way unevenly along the edge of"
                + " the water. A little to the south, a stream is"
                + " visible trailing out of the woods to meet with"
                + " the edge of the lake.");

    add_item( ({"stream"}), BSN(
        "A short distance to the south, a stream is visible trailing"
      + " out of the woods to join with the waters of Del Rimmon."));
    add_item( ({"woods"}), BSN(
        "The woods to the west run the length of the shoreline as one"
      + " travels north and south. It is broken slightly where a stream"
      + " passes through its trees to join with the waters of the lake"
      + " a bit to the south."));
    add_item( ({"edge of the water", "edge of the lake"}), BSN(
        "The edge of the lake runs smoothly past to the north and"
      + " south. It is interrupted slightly by a stream which runs"
      + " to meet it along the shore south of here."));
    add_item( ({"ground"}), BSN(
        "The shoreline here is composed of many pebbles, smaller than"
      + " rocks, but much larger than sand. They run up from the"
      + " water to meet with the banks which run down from the"
      + " steep hillsides. There appear to be footprints of some"
      + " kind in the ground here."));
    add_item( ({"footprint", "footprints"}), BSN(
        "Unfortunately, the ground is not muddy enough to provide"
      + " much of a clue as to what the feet which made these"
      + " prints may have looked like. It is obvious that they"
      + " were made by something walking on two, rather than four"
      + " legs."));

    add_cmd_item( ({"footprint", "footprints", "ground"}),
        ({"search"}), BSN(
        "There are many footprints in the pebbles, but they are"
      + " not clear enough to get any real indication of what"
      + " might have made them. They seem to be heading into the"
      + " trees to the west."));

    add_exit(DELRIMMON_DIR + "lakeside/nw_shore1","northeast");
    add_exit(DELRIMMON_DIR + "lakeside/w_shore4","south");
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4","southwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1b","northwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1","north",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "east", "southeast" }),
        "You look briefly at the water lapping at the shore in that"
      + " direction, and think better of it.\n");
}

/*
 * Function name: follow_footprints
 * Description  : allows players to attempt to follow the footprints
 *                on the ground into the woods if they have the
 *                required tracking skill.
 * Arguments    : str (string) - what the player typed after 'follow'
 * Returns      : 1 - success, 0 - failure
 */
int
follow_footprints(string str)
{
    if (!strlen(str))
        NFN0("Follow what?");

    if (str != "tracks" && str != "prints" && str != "footprints")
        NFN0("What do you wish to follow?");

    if (TP->query_skill(SS_TRACKING) < 15 + random(5) )
        NFN0("You follow the tracks a little ways away from the"
           + " shore, where they become confusing, and you lose"
           + " the trail.");

    write("You expertly follow the tracks into the woods.\n");
    TP->command("$west");

    return 1;
}

/*
 * Function name: init
 * Description  : allows us to add "follow" as a mortal action
 */
void
init()
{
    ::init();

    add_action(follow_footprints, "follow");
}
