/*
 *  /d/Emerald/telberin/telberin_lookout.c
 *
 *  This is the view given from the torque which has been placed
 *  upon the uppermost spire of the Royal Palace in Telberin.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

/* prototypes */
public string        describe_area();
public void          create_emerald_room();
public void          reset_room();


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room, using domain presets
 */
public void
create_emerald_room()
{
    set_short("a spectacular view from high above the city of Telberin");
    set_long(describe_area);

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_emerald_room */


/*
 * Function name:        describe_area
 * Description  :        shows us the players who are in Telberin.
 * Returns      :        string - a description of the above stated
 */
public string
describe_area()
{
    object *ppl = get_players_in_dir("/d/Emerald/telberin/*");
    object *visible = filter(ppl, not @ &->query_prop(ROOM_I_INSIDE) @
        environment);
    string  desc;

    desc = "Spread out before your eyes is the city of Telberin,"
      + " stretching out beneath you like a map. This vantage point"
      + " is high above the city, perhaps atop one of the high"
      + " pinnacles of the Royal Palace, bits of which are visible"
      + " directly below you. The view slowly rotates until the"
      + " entire city has passed your vision, which appears somehow"
      + " enhanced as if by some enchantment to increase the clarity"
      + " of tiny details on the streets below. Everyone in the"
      + " area is easily within your ability to detect. ";

    if (COMPOSITE_LIVE(visible) != "nobody")
    {
        desc += "You are able to see " + COMPOSITE_LIVE(visible)
              + " walking the city streets.\n";
    }
    else
    {
        desc += "You do not see anyone other than the elves who inhabit"
              + " the city in the area at present.\n";
    }

    return desc;
} /* describe_area */


/*
 * Function name:        reset_room
 * Description  :        clone the torque and its pillar to the room
 */
public void
reset_room()
{
    object torque;

    if (!present("_telberin_torque"))
    {
        torque = clone_object(
            "/d/Emerald/torque/unique_torques/telberin_torque");
        torque->set_no_show(1);
        torque->move(this_object());
    }
} /* reset_room */
