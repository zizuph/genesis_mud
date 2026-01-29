/*
 *  /d/Emerald/north_shore/outpost/gate01.c
 *
 *  This area was originally created by Mhyrkhaan in November of
 *  1998 and then put on hold. That wizard has since left the
 *  Emerald domain, and so I have decided to put his work to some
 *  use as a small killing area to give some small satisfaction
 *  to players who value that sort of thing. The descriptions
 *  and items have been updated by Gorboth.
 *
 *  Update August 2003 (Gorboth)
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;


/*
 * Function name:    create_outpost_outside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_outside_room()
{
    set_short("outside the gates of a damaged outpost");
    set_em_long("A large outpost stands directly to the"
      + " north. Its open and broken gates grant access into"
      + " what was obviously once a formidable outpost guarding"
      + " these northern shores of Lake Telberin. A path leads"
      + " along the lakeshore to the west towards a dock which"
      + " is visible in that direction.\n");

    add_outpost_items();
    add_lakeview();

    add_exit("gate02", "north", 0, 1, 1);
    add_exit("/d/Emerald/north_shore/dock", "west");

    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_no_exit_msg( ({ "northwest", "northeast" }),
        "You walk a ways along the line of the outpost wall, and"
      + " then return to the path before the gates.\n");
    set_no_exit_msg( ({ "east" }),
        "You wander a ways toward the forest, but find nothing"
      + " of interest, and return to the gates of the outpost.\n");
    set_no_exit_msg( ({ "southwest", "southeast", "south" }),
        "You pause at the edge of the lake, and decide not to"
      + " continue.\n");
} /* create_outpost_outside_room */


/* 
 * Function name:        enter_outpost
 * Description  :        allow players to use the 'enter' command
 *                       to enter the outpsot
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
enter_outpost(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [large] [elven] [elvish] 'outpost' / 'fortress'"
      + " / 'gate' / 'gates' [of] [the] [outpost]"))
    {
        return 0; /* can't parse the player syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'north' here using"
          + " command(). Since you are a wizard, that will not work."
          + " Simply go 'north' yourself.\n");
        return 1;
    }

    this_player()->command("north");
    return 1;
} /* enter_outpost */


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
        "[from] [the] 'water' / 'lake' [from] [the] [lake]"
      + " [telberin]"))
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
        write("You scoop a handful of lake water, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You seem to have drunk your fill.\n");
    }
    else
    {
        write("You scoop a handful of lake water, and sip it"
            + " cautiously. It is icy cold, and very refreshing."
            + " You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " stoops and drinks some water"
        + " from the lake.\n");

    return 1;
} /* do_drink */


/*
 * Function name:        do_swim
 * Description  :        allow the player to try to swim
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
do_swim(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Swim where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [to] [into] [the] 'water' / 'lake' [telberin]"))
    {
        return 0; /* can't parse the syntax */
    }

    this_player()->command("south"); /* easiest method */
    return 1;
} /* do_swim */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_swim, "swim");
    add_action(do_swim, "dive");
    add_action(do_drink, "drink");
    add_action(enter_outpost, "enter");
} /* init */
