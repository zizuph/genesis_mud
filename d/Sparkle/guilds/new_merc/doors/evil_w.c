/*
 *  /d/Sparkle/guilds/new_merc/doors/evil_e.c
 *
 *  This is the west side of the door to the evil bunk and droproom
 *  in the Mercenary Guildhall.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
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

    set_door_id("evil_start");
    set_pass_command( ({ "e" ,"east" }) );
    set_door_name( ({ "door", "ash-grey door", "stained door",
                      "doorway", "ash-grey doorway", "stained doorway",
                      "very stained door", "very stained ash-grey door",
                      "very stained doorway",
                      "very stained ash-grey doorway",
                      "east door", "eastern door",
                      "door to the east" }) );

    set_open_desc("There is an open ash-grey door leading east.\n");
    set_closed_desc("There is a closed ash-grey door leading east.\n");

    set_fail_pass("The ash-grey door is closed.\n");
    set_open_mess( ({ "opens the ash-grey door.\n",
                      "The ash-grey door closes.\n" }) );
    set_close_mess( ({ "closes the ash-grey door.\n",
                       "The ash-grey door closes.\n" }) );

    set_door_desc("A stained ash-grey door is set into the east wall"
      + " of this room. The color reminds you of the last enemy you"
      + " set fire to ... ah ... comforting.\n");

    set_other_room(ROOM_DIR + "s_hallway");

    set_open(0);
    set_locked(0);
} /* create_door */