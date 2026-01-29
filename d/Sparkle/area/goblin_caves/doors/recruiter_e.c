/*
 *
 *  recruiter door - inner side
 *
 *  Boreaulam - May 2012
 */
#pragma strict_types

inherit "/std/door";

#include "defs.h"

/*
 * Function name:        create_door
 * Description  :        constructor for the door object
 */
public void
create_door()
{
    ::create_door();

    set_door_id("goblin_recruiter_door");
    set_pass_command( ({ "w", "west" }) );
    set_door_name( ({ "door", "west door", "western door", }) );

    set_open_desc("There is an open door leading west.\n");
    set_closed_desc("There is a closed door leading west.\n");

    set_fail_pass("The door is closed.\n");
    set_open_mess( ({ "opens the door.\n",
                      "The door closes.\n" }) );
    set_close_mess( ({ "closes the door.\n",
                       "The door closes.\n" }) );

    set_door_desc("A door is set in the west wall of " +
                  "the cave.\n");

    set_other_room(ROOMS_DIR + "level1/rooml");

    set_open(0);
    set_locked(0);
} /* create_door */