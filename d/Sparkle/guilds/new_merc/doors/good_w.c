/*
 *  /d/Sparkle/guilds/new_merc/doors/good_w.c
 *
 *  This is the east side of the door to the good bunk and droproom
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

    set_door_id("good_start");
    set_pass_command( ({ "e" ,"east" }) );
    set_door_name( ({ "door", "polished door", "beautiful door",
                      "doorway", "polished doorway", "beautiful doorway",
                      "very beautiful door", "very beautiful polished door",
                      "very beautiful doorway",
                      "very beautiful polished doorway",
                      "east door", "eastern door",
                      "door to the east" }) );

    set_open_desc("There is an open polished door leading east.\n");
    set_closed_desc("There is a closed polished door leading east.\n");

    set_fail_pass("The polished door is closed.\n");
    set_open_mess( ({ "opens the polished door.\n",
                      "The polished door closes.\n" }) );
    set_close_mess( ({ "closes the polished door.\n",
                       "The polished door closes.\n" }) );

    set_door_desc("A beautiful polished door is set into the east wall"
      + " of this room. It is fitting that someone would take the"
      + " time to create something of beauty to mark the border"
      + " of this area of the lodge.\n");

    set_other_room(ROOM_DIR + "n_hallway");

    set_open(0);
    set_locked(0);
} /* create_door */