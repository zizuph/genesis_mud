/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/parth1.c
 *
 *  This is the southernmost area of shore along the lake of Del
 *  Rimmon. A stream runs down to the water here. This is also the
 *  room most players will see first, assuming they enter the area by
 *  normal means.
 *
 *  Copyright (c) September 1997 by Cooper Sherry (Gorboth)
 *  Added fishing     : August 2021 (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeshore";
#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/sys/paths.h"


/* prototypes */
void           create_lakeshore();
public int     do_drink(string str);
public void    init();


/*
 * Function name: create_lakeshore
 * Description  : allow us to create the room with area presets
 */
void
create_lakeshore()
{
    set_loc(1);
    set_side("southwest");

    set_extraline("A green lawn runs down to the water here from"
                + " the feet of Melan Rath, whose first gentle"
                + " slopes rise to the south, clad with trees"
                + " which can be seen marching away westward"
                + " along the curving shores of the lake. A little"
                + " spring falls tumbling down to feed the grass"
                + " here, just beside a path which leads up the hillside"
                + " to the south.");

    add_item( ({ "path", "pathway" }),
        "A path leads down to this shore from the southern hillside."
      + " It looks as if it has not been used much over the last"
      + " hundred or so years.\n");
    add_item( ({ "blade", "blades", "blades of grass", "grass blade",
                 "grass blades" }), BSN(
        "The blades of grass are thick and deep green, having been"
      + " very thoroughly nourished by the constant presence of water"
      + " in the ground."));
    add_item( ({ "lake water", "water from the lake",
                 "water of the lake" }), BSN(
        "The water of the lake has seeped into the the ground,"
      + " providing a constant source of nourishment for the lawn"
      + " here."));
    add_item( ({"spring", "little spring", "springs"}), BSN(
        "The spring is too small to be called a stream, but it"
      + " has nevertheless worn away a very narrow gully in"
      + " the rocks which outline the rising slopes to the"
      + " south."));
    add_item( ({"rising slopes", "rocks", "rock"}), BSN(
        "Outcroppings of stone issue forth from the otherwise"
      + " grassy slopes along Melan Rath to the south and west. They"
      + " glisten with moisture where a little spring trickles"
      + " down from above in that direction."));
    add_item( ({"outcroppings", "outcroppings of stone",
                "stone", "stones"}), BSN(
        "The grassy slopes which rise at the base of Melan Rath to"
      + " the south are marked in places by outcroppings of weather-"
      + "worn rock. A spring winds its way among the stones."));
    add_item( ({"lawn", "green lawn", "lawns", "parth galen"}), BSN(
        "This lawn is extremely lush and fair, almost seeming to"
      + " have been cared for by forces other than those of nature."
      + " It extends a bit further to the west, curving slightly"
      + " along the edge of the lake."));
    add_item( ({"gully", "gullies"}), BSN(
        "The gully is little more than a groove which has been worn"
      + " in the rocks at the base of Melan Rath."));
    add_item( ({"groove", "grooves"}), BSN(
        "The groove in the rocks runs down with the spring water"
      + " to the edge of the lawn where the water soaks into the"
      + " grass."));

    add_cmd_item( ({"spring", "little spring", "springs", "gully"}),
                  ({"search", "dig"}), BSN(
        "There does not seem to be anything out of the"
      + " ordinary when you dig a bit in the rocky places"
      + " where the spring trickles down to meet the grass."));


    add_exit(DELRIMMON_DIR + "lakeside/pathway3","south");
    add_exit(DELRIMMON_DIR + "lakeside/sw_shore2","west");
    add_exit(DELRIMMON_DIR + "lakeside/sw_cliff1","southwest",0,1,1);

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "northwest", "north", "northeast" }),
        "You wade a few feet into the waters of Del Rimmon, and then"
      + " head back to shore.\n");
    set_no_exit_msg( ({ "east", "southeast" }),
        "Large outcroppings of stone rise between here and the waters"
      + " of the lake to the east, blocking your movement.\n");
} /* create_lakeshore */


/*
 * Function name:        do_drink
 * Description  :        let players drink from the spring
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'spring' / 'stream' [from] [the]"
      + " [stream] [spring]"))
    {
        notify_fail("What do you wish to drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("You scoop a handful of spring water, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You seem to have drunk your fill.\n");
    }
    else
    {
        write("You scoop a handful of spring water, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " stoops and drinks some water"
        + " from a nearby spring.\n");

    return 1;
} /* do_drink */


/*
 * Function name:        init
 * Description  :        set up actions for the players
 */
public void
init()
{
    ::init();

    add_action(do_drink, "drink");
} /* init */
