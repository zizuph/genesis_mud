/*
 * cave38.c
 *
 * wolf lair
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
    ::create_terel_room();
    set_long(query_long() +
        "The tunnel ends here. To the west is the exit back "+
        "towards the main section of the caves. A bed of hay "+
        "can be seen on a ledge within the wall. Several bones "+
        "have been strewn about the room.\n");

    add_item("bones",
        "The bones have been chewed on by something " +
        "with very large sharp teeth.\n");

    add_item(({"bed","hay","bed of hay"}),
        "Something has formed a bed out of a stack of hay within "+
        "a ledge of one of the walls in the cave.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave37","west");

    add_npc(MOUNTAIN_DIR + "goblincave/monster/bigwolf");
}
