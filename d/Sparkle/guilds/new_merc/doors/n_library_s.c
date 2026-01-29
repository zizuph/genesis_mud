/*
 *  /d/Sparkle/guilds/new_merc/doors/n_library_s.c
 *
 *  This is the south side of the door to the north entrance to the
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
    set_pass_command( ({ "n" ,"north" }) );
    set_door_name( ({ "door", "pine door", "attractive door",
                      "doorway", "pine doorway", "attractive doorway",
                      "very attractive door", "very attractive pine door",
                      "very attractive doorway",
                      "very attractive pine doorway",
                      "north door", "northern door",
                      "door to the north" }) );

    set_open_desc("There is an open pine door leading north.\n");
    set_closed_desc("There is a closed pine door leading north.\n");

    set_fail_pass("The pine door is closed.\n");
    set_open_mess( ({ "opens the pine door.\n",
                      "The pine door closes.\n" }) );
    set_close_mess( ({ "closes the pine door.\n",
                       "The pine door closes.\n" }) );

    set_door_desc("A attractive pine door is set into the north wall"
      + " of the library. It isn't particularly beautiful, but"
      + " the wood is extremely attractive.\n");

    set_other_room(ROOM_DIR + "n_hallway");

    set_open(0);
    set_locked(0);
} /* create_door */


/*
 * Function name: pass_door
 * Description:   Pass the door. Wizards can pass the door by giving the
 *                command with an exclamation point.
 * Arguments:     arg - arguments given
 *
 * I mask this to include a check for players leaving with a library
 * book.
 */
int
pass_door(string arg)
{
    if (present("_merc_library_book", this_player()) ||
        present("_merc_library_book", deep_inventory(this_player())))
    {
        write("The librarian says: Please <return> any books you have"
          + " before leaving.\n");

        return 1;
    }

    return ::pass_door(arg);
} /* pass_door */