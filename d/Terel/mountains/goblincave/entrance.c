/*
 * entrance.c
 *
 * Entance to the orc cave.  Since the cave is dark inside, we put
 * two torches here so players without a light source can find their
 * way.
 * Modified by Tomas for Goblin Cave use.  --  Dec. 1999
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    FIX_EUID;
    ::create_terel_room();

    set_short("cave entrance");
    set_long(query_long() +
        "Behind you, to the west, you can see the bright opening " +
        "leading out.\n");

    add_exit(MOUNTAIN_DIR + "goblincave/cave02", "east", 0);
    add_exit(MOUNTAIN_DIR + "clifftop", "west", 0);

    reset_room();
}

/*
 * Function name: reset_room
 * Description:   put two torches here at each reset
 */
public void
reset_terel_room()
{
    if (present("torch"))
        return;

    object torch = clone_object("/std/torch");
    torch->set_long("It's a standard torch.\n");
    torch->move(TO);

    torch = clone_object("/std/torch");
    torch->set_long("It's a standard torch.\n");
    torch->move(TO);
}
