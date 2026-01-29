/*
 *  /d/Emerald/telberin/dock/telberin_dock.c
 *
 *  This is the main entrypoint into Emerald at present. Players may
 *  take the ship from Sparkle to land at this point outside of
 *  Telberin, or return from here to Sparkle.
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 *
 *  Revision history: Aug 2021 - Added fishing (Gorboth)
 *
 * Converted to the new ship system by Tapakah, 10/2008
 * Added exit to the circle dock, Tapakah, 05/2009
 */
#pragma strict_types

#include <stdproperties.h>
#include <time.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/telberin/dock/dockview";
inherit LIBPIER;

/* prototypes */
public void        create_emerald_room();
public string      read_sign();

/*
 * Function nane:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("on the main dock of Telberin");
    set_em_long("This dock extends along the shore of the island,"
      + " providing ample mooring for the various ships which are"
      + " docked along its length. South of here, a road travels up"
      + " the slope of a hill leading to the main gates of the city"
      + " of Telberin which rises majestically in the distance. A"
      + " small pier runs north of here, out into the waters of the"
      + " lake. A sign is fixed to a nearby post.\n");

    add_dock_stuff();

    try_item( ({ "sign", "signpost", "post", "nearby post" }),
        read_sign);
    add_cmd_item( ({ "sign", "signpost" }),
                  ({ "read" }), read_sign);

    add_exit("ferry_dock", "north");
    add_exit("rmc_dock", "east");
    add_exit("circle_dock", "west");
    add_exit("telberin_gates", "south");

    add_prop("_live_i_can_fish", "freshwater");
    add_prop(ROOM_I_LIGHT, 9);
    add_prop(ROOM_I_NO_CLEANUP, 1); /* must not be unloaded */
    reset_room();

    // Pier specific calls
    add_pier_entry(MASTER_OB(this_object()), "Telberin", "Pier to Sparkle");    
    initialize_pier();
} /* create_emerald_room */

/*
 * Function name:        read_sign
 * Description  :        show the sign, in fun text graphics
 * Returns      :        string - the sign text
 */
public string
read_sign()
{
    string desc;

    desc = "\n\n"
     + "          _____________________________\n"
     + "        .'                             `.\n"
     + "        |      Passage to Sparkle       |\n"
     + "        |       Price: 30 copper        |\n"
     + "        `._____________________________.'\n\n";

    return desc;
} /* read_sign */


/*
 * Function name:        do_dive
 * Description  :        allow the player to try to dive off the pier,
 *                       but inform him/her that that won't be possible
 * Arguments    :        string arg - what the player typed
 * Return       :        int 1 - success, 0 - failure
 */
public int
do_dive(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[off] [in] [to] [into] [the] 'lake' / 'water' / 'pier'"
      + " [telberin]"))
    {
        return 0; /* couldn't parse the player syntax */
    }

    write("Just as you are about to dive in, you notice that there"
      + " is no ladder by which you could climb back up. It would"
      + " be a long and unpleasant swim back to shore, so you"
      + " step back again.\n");
    return 1;
} /* do_dive */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_dive, "swim");
    add_action(do_dive, "dive");
} /* init */
