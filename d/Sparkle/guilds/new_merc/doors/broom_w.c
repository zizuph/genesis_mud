/*
 *  /d/Sparkle/guilds/new_merc/doors/broom_w.c
 *
 *  This is the west side of the broom closet located in the
 *  neutral sleeping quarters of the Mercenary Guild.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/door";

#include "../merc_defs.h"

/* Prototypes */
public void        create_door();


/*
 * Function name:        create_door
 * Description  :        constructor for the door object
 */
public void
create_door()
{
    ::create_door();

    set_door_id("broom_closet");
    set_pass_command( ({ "e", "east" }) );
    set_door_name( ({ "door", "blue door", "painted blue door",
                      "blue painted door",
                      "doorway", "blue doorway", "painted doorway",
                      "painted blue doorway",
                      "east door", "eastern door",
                      "door to the east",
                      "narrow door", "fairly narrow door",
                      "narrow doorway", "fairly narrow doorway" }) );

    set_open_desc("There is an open blue door leading east.\n");
    set_closed_desc("There is a closed blue door leading east.\n");

    set_fail_pass("The blue door is closed.\n");
    set_open_mess( ({ "opens the blue door.\n",
                      "The blue door closes.\n" }) );
    set_close_mess( ({ "closes the blue door.\n",
                       "The blue door closes.\n" }) );

    set_door_desc("A fairly narrow door is set in the east wall of"
      + " these sleeping chambers. It has been painted blue.\n");

    set_other_room(ROOM_DIR + "broom_closet");

    set_open(0);
    set_locked(0);
} /* create_door */