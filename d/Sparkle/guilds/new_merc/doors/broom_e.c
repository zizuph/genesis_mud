/*
 *  /d/Sparkle/guilds/new_merc/doors/broom_e.c
 *
 *  This is the west side of the broom closet door located in the
 *  broom closet of the Mercenary Guild itself.
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
    set_pass_command( ({ "w", "west" }) );
    set_door_name( ({ "door", "blue door", "painted blue door",
                      "blue painted door",
                      "doorway", "blue doorway", "painted doorway",
                      "painted blue doorway",
                      "west door", "western door",
                      "door to the west",
                      "narrow door", "fairly narrow door",
                      "narrow doorway", "fairly narrow doorway" }) );

    set_open_desc("There is an open blue door leading west.\n");
    set_closed_desc("There is a closed blue door leading west.\n");

    set_fail_pass("The blue door is closed.\n");
    set_open_mess( ({ "opens the blue door.\n",
                      "The blue door closes.\n" }) );
    set_close_mess( ({ "closes the blue door.\n",
                       "The blue door closes.\n" }) );

    set_door_desc("A fairly narrow door is set in the west wall of"
      + " this closet. It has been painted blue.\n");

    set_other_room(ROOM_DIR + "neutral_start");

    set_open(0);
    set_locked(0);
} /* create_door */