/*
 *  /d/Sparkle/guilds/new_merc/doors/s_library_s.c
 *
 *  This is the south side of the door to the south entrance to the
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

    set_door_id("s_library");
    set_pass_command( ({ "n" ,"north" }) );
    set_door_name( ({ "door", "oak door", "handsome door",
                      "doorway", "oak doorway", "handsome doorway",
                      "very handsome door", "very handsome oak door",
                      "very handsome doorway",
                      "very handsome oak doorway",
                      "north door", "northern door",
                      "door to the north" }) );

    set_open_desc("There is an open oak door leading north.\n");
    set_closed_desc("There is a closed oak door leading north.\n");

    set_fail_pass("The oak door is closed.\n");
    set_open_mess( ({ "opens the oak door.\n",
                      "The oak door closes.\n" }) );
    set_close_mess( ({ "closes the oak door.\n",
                       "The oak door closes.\n" }) );

    set_door_desc("A handsome oak door is set into the north wall"
      + " of this corridor. It isn't particularly beautiful, but"
      + " the wood is extremely attractive.\n");

    set_other_room(ROOM_DIR + "library");

    set_open(0);
    set_locked(0);
} /* create_door */