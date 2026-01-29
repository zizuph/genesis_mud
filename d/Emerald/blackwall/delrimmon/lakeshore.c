/*
 *  /d/Emerald/blackwall/delrimmon/lakeshore.c
 *
 *  This file is intended to make available the searching for
 *  skipping stones in the lakeshore rooms along Del Rimmon.
 *
 *  Copyright (c) October 1997 by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/legacy/random_noise";

#include <macros.h>
#include <stdproperties.h>      /* for OBJ_S_SEARCH_FUN, etc    */
#include <ss_types.h>                   /* for SS_AWARENESS     */

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define  NSTONES   20       /* There are random(NSTONES) stones */
#define  CATAPULT_NPC_FILE  (DELRIMMON_DIR + "npc/catapult_orc")

/* global variables */
int     Nstones = random(NSTONES) + 10;
object *Catapult_npcs;

/* prototypes */
public void    create_lakeshore();
nomask void    create_del_rimmon();
public string  do_search(object tp, string arg);
public int     random_noise();
public void    init();
public int     do_drink(string str);
public int     swim_message(string arg);
public void    reset_room();
public void    clone_catapult_orcs();
public int     catapult_arm_landing(object destination);

public int  query_stones() { return Nstones; }

/*
 * function name:        create_lakeshore
 * description  :        our dummy routine for inheriting rooms
 */
public void
create_lakeshore()
{
} /* create_lakeshore */

/*
 * function name:        create_del_rimmon
 * description  :        set up the room with domain presets
 */
nomask void
create_del_rimmon()
{
    set_short(del_rimmon_short);
    set_long(del_rimmon_long);

    add_name("emerald_lakeshore");   /* for stone skipping */

    create_lakeshore();

    add_view();

    try_item( ({"rimmon", "rimmon falls", "waterfall", "falls",
                "great waterfall", "great falls"}), BSN(
        "Though it is not visible from this distance, the rumour"
      + " is strong of Rimmon Falls, which booms endlessly as its"
      + " sluice empties the waters of Del Rimmon to the depths"
      + " below the Blackwall Mountains to the distant south."));

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 3);
} /* create_del_rimmon */

/*
 * function name:        do_search
 * description  :        allow the player to search the beach for
 *                       skipping stones. :-)
 * arguments    :        tp -- the person searching
 *                       arg -- what they typed
 * returns      :        1 -- success, 0 -- failure
 */
public string
do_search(object tp, string arg)
{
    int     n;
    object  stone;
    string  type,
            where,
            what;

    if ( !strlen(arg) )
        return "";

    // Allow "search [pebbled|muddy]
    //               beach[es]|bank[s]|shore[s]|lakeshore[s]|ground
    //               [ for stone[s]|pebble[s]|rock[s] ]"
    if ( (n = sscanf(arg, "%s %s for %s", type, where, what)) == 3 ||
         (n = sscanf(arg, "%s for %s", where, what)) == 2 )
    {
        if ( what != "stone" && what != "stones" &&
             what != "pebble" && what != "pebbles" &&
             what != "rock" && what != "rocks" )
                return "";
    }
    else
        where = arg;
    if ( where != "beach" && where != "beaches" &&
         where != "bank" && where != "banks" &&
         where != "shore" && where != "shores" &&
         where != "lakeshore" && where != "lakeshores" &&
         where != "ground" && where != "pebble" && where != "pebbles" )
        return "";
    if ( n == 3 && type != "muddy" && type != "pebbled" )
        return "";

    if ( Nstones > 0 &&
    TP->query_skill(SS_AWARENESS) >= (MIN_AWARE + random(RANDOM_AWARE)) &&
    objectp(stone = clone_object(DELRIMMON_DIR + "obj/skipping_stone")) )
    {
        --Nstones;
        what = BSN("You search around for a while, until you find"
                  + " a rather attractive stone on the ground.");
        tell_room(environment(this_player()), QCTNAME(this_player())
          + " searches around, and picks a stone up from the beach.\n",
            this_player());

        if ( stone->move(TP) )
        {
            what += BSN("Oops, you dropped the stone.");
            tell_room(environment(this_player()), QCTNAME(this_player())
              + " drops a stone.\n", this_player());
            stone->move(TO);
        }
    }
    else
        what = BSN("You find nothing of interest.");

    return what;
} /* do_search */

/*
 * Function name: random_noise
 * Description  : allows us to let the player hear the falls of Rimmon
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    string  distance;

    switch(query_side())
    {
        case "southwest":
        {
            distance = "thunderous";
            break;
        }
        case "west":
        {
            distance = "loud";
            break;
        }
        case "northwest":
        {
            distance = "faint";
            break;
        }
        default:
        {
            distance = "loud";
            break;
        }
    }

    tell_room(TO, BSN(      ({
        "In the distance, a " +distance+ " rumbling echoes along the"
      + " lakeshore.",
        "The " +distance+ " voice of Rimmon Falls rumbles to the"
      + " southeast.",
        "Calling out in a " +distance+ " rumble, a great waterfall"
      + " can be heard along the lakeshore.",
        "Endlessly rolling over the lake, the " +distance+ " voice"
      + " of Rimmon Falls can be heard in the distance.",
        "A deep and throbbing rumble echoes across the lakeshore.",
        })[random(4)] ) );
    return 1;
} /* random_noise */

/*
 * Function name:   init
 * Description  :   init the random noises, and drinking
 */
public void
init()
{
    ::init();
    init_random_noise();

    add_action(swim_message, "swim");
    add_action(swim_message, "dive");
    add_action(do_drink, "drink");
} /* init */


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
        "[from] [the] 'water' / 'lake' / 'del' [from]"
      + " [the] [lake] [del] [rimmon]"))
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
 * Function name:        swim_message
 * Description  :        tells players that they can't swim in the lake
 * Arguments    :        string arg - what the player typed
 * Returns      :        string - the message
 */
public int
swim_message(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Where to you want to " + QVB + "?");
    }

    if (!parse_command(arg, ({}),
        "[out] [in] [into] [across] [the]"
      + " 'lake' / 'water' / 'del' [rimmon]"))
    {
        return 0;
    }

    write("The lake is far too large to swim across, and there seems"
        + " to be no other point in getting wet.\n");
    return 1;
} /* swim_message */


/*
 * function name:        reset_room
 * description  :        renew the amount of skipping stones at reset
 */
public void
reset_room()
{
    Nstones = random(NSTONES) + 10;
} /* reset_room */

/*
 * function name:        clone_catapult_orcs
 * description  :        called by /d/Emerald/blackwall/delrimmon/obj/catapult.c,
 *                       this routine summons some curious orcs to see
 *                       what just flew through the air and landed
 *                       in the room.
 */
public void
clone_catapult_orcs()
{
    if (!sizeof(Catapult_npcs))
        Catapult_npcs = allocate(2 + random(3));

    set_alarm(4.0, 0.0, &clone_npcs(Catapult_npcs,
              CATAPULT_NPC_FILE, 3.0));

    return;
} /* clone_catapult_orcs */

/*
 * function name:        catapult_arm_landing
 * description  :        called by /d/Emerald/blackwall/delrimmon/obj/catapult.c,
 *                       this routine sends a piece of the broken
 *                       catapult flying into the room, and then
 *                       calls clone_catapult_orcs to rouse some
 *                       of the local gentry
 * arguments    :        object destination -- the room in which this
 *                                             is happening
 * returns      :        1 - success
 */
public int
catapult_arm_landing(object destination)
{
    tell_room(destination, BSN("With a loud snapping of branches, a"
      + " large woodem beam comes crashing through the woods of"
      + " of the hillside and tumbles to a halt on the bank of"
      + " the lake here."));

    clone_object(DELRIMMON_DIR + "obj/wep/catapult_arm")->move(TO);
    clone_catapult_orcs();

    return 1;
} /* catapult_arm_landing */
