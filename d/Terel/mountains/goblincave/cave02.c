/*
 * cave02.c
 *
 * A cave room near the entrance.
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";


/*
 * Function name: do_listen
 * Description:   Handle the listen action
 * Returns:       1/0
 */
public int
do_listen(string str)
{
    write("It sounds like a lot of bats are nearby to the east.\n");
    tell_room(ETP, QCTNAME(TP) + " listens to the east.\n", TP);
    return 1;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init()
{
    ::init();
    add_action(do_listen, "listen");
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "Everything is very quiet around here.  Faint high "+
        "pitched sounds can be heard from the east.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave03",   "east");
    add_exit(MOUNTAIN_DIR + "goblincave/entrance", "west");
    add_exit(MOUNTAIN_DIR + "goblincave/cave23", "northwest");
    add_exit(MOUNTAIN_DIR + "goblincave/cave24", "southwest");
}
