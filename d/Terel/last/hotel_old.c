/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * hotel3.c
 *
 * A hotel room.
 */

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR + "hotel_room";

static int open = 0;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LAST_DIR + "whdragon",  "southwest", 0);
}

/*
init()
{
    ::init();
    add_action("do_clap", "clap");
}
*/

public int
do_clap(string str)
{
    set_alarm(3.0, -1.0, "secret");
}

public void
secret()
{
    if (open > 0) {
        tell_room(TO, "A secret passage closes.\n");
        remove_exit("north");
        open = 0;
        return;
    }
    tell_room(TO, "A secret passage opens to the north.\n");
    add_exit("/d/Terel/last/hotel_hid", "north", 0);
    open = 1;
}


