/*
 *  /d/Sparkle/guilds/new_merc/doors/kitchen_s.c
 *
 *  This is the south side of the door to the kitchen from outside
 *  the Mercenary Guild Hall.
 *
 *  Created September 2009, by Cooper Sherry (Gorboth)
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

    set_door_id("kitchen");
    set_pass_command( ({ "n" ,"north" }) );
    set_door_name( ({ "door", "wooden door", "rough door",
                      "doorway", "wooden doorway", "rough doorway",
                      "very rough door", "very rough wooden door",
                      "very rough doorway",
                      "very rough wooden doorway",
                      "north door", "northern door",
                      "door to the north" }) );

    set_open_desc("There is an open wooden door leading north.\n");
    set_closed_desc("There is a closed wooden door leading north.\n");

    set_fail_pass("The wooden door is closed.\n");
    set_open_mess( ({ "opens the wooden door.\n",
                      "The wooden door closes.\n" }) );
    set_close_mess( ({ "closes the wooden door.\n",
                       "The wooden door closes.\n" }) );

    set_door_desc("A rough wooden door is set into the north wall of"
      + " the kitchen.\n");

    set_other_room(ROOM_DIR + "wep_train");

    set_open(0);
    set_locked(0);
} /* create_door */
