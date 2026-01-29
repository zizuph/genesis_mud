/*
 *  /d/Sparkle/guilds/new_merc/doors/n_library_n.c
 *
 *  This is the north side of the door to the north entrance to the
 *  library in the Mercenary Guildhall.
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

    set_door_id("n_library");
    set_pass_command( ({ "s" ,"south" }) );
    set_door_name( ({ "door", "pine door", "attractive door",
                      "doorway", "pine doorway", "attractive doorway",
                      "very attractive door", "very attractive pine door",
                      "very attractive doorway",
                      "very attractive pine doorway",
                      "south door", "southern door",
                      "door to the south" }) );

    set_open_desc("There is an open pine door leading south.\n");
    set_closed_desc("There is a closed pine door leading south.\n");

    set_fail_pass("The pine door is closed.\n");
    set_open_mess( ({ "opens the pine door.\n",
                      "The pine door closes.\n" }) );
    set_close_mess( ({ "closes the pine door.\n",
                       "The pine door closes.\n" }) );

    set_door_desc("A attractive pine door is set into the south wall"
      + " of the corridor. It isn't particularly beautiful, but"
      + " the wood is extremely attractive.\n");

    set_other_room(ROOM_DIR + "library");

    set_open(0);
    set_locked(0);
} /* create_door */