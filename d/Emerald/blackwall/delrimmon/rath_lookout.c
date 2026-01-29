/*
 *  /d/Emerald/blackwall/delrimmon/rath_lookout.c
 *
 *  This is the view given from the torque which has been placed
 *  upon the summit of Melan Rath.
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
public void        reset_room();


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room, using domain presets
 */
public void
create_emerald_room()
{
    set_short("a glorious view from high above the lake of Del Rimmon");
    set_long(describe_area);

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_emerald_room */


/*
 * Function name:        describe_area
 * Description  :        shows us the players who are in the Del
 *                       Rimmon area, and where they are,
 *                       approximately.
 * Returns      :        string - a description of the above stated
 */
public string
describe_area()
{
    object *ppl = get_players_in_dir(
        "/d/Emerald/blackwall/delrimmon/*");
    object *visible = filter(ppl, not @ &->query_prop(ROOM_I_INSIDE) @
        environment);
    string  desc;

    desc = "You see, as if from a great height, the lake of Del Rimmon"
      + " and its surroundings. The entire area is visible in perfect"
      + " clarity, and almost seems magnified by some form of"
      + " enchantment. Even far off details are readily accessible to"
      + " your sight from this vantage point. ";

    if (COMPOSITE_LIVE(visible) != "nobody")
    {
        desc += "You are able to see " + COMPOSITE_LIVE(visible)
              + " in the hills to the west of the lake.\n";
    }
    else
    {
        desc += "You do not see anyone in the area at present.\n";
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
    object corpse,
           torque;


    if (!present("_rath_torque"))
    {
        torque = clone_object(
            "/d/Emerald/torque/unique_torques/rath_torque");
        torque->set_no_show(1);
        torque->move(this_object());
    }
} /* reset_room */
