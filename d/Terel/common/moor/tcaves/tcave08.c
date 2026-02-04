/*
 * tcave08.c
 *
 * Lucius - Jan 2021
 *    Modernized
 */
#include "/d/Terel/include/Terel.h"
inherit TROLL_CAVE_DIR + "tcave_room";
/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "You have reached a large cavern. The main cavern of this lair. "+
        "You may only move in two directions from this room south "+
        "or southwest.\n");

    add_exit(TROLL_CAVE_DIR + "tcave06", "southwest");
    add_exit(TROLL_CAVE_DIR + "tcave07",   "south");

    add_object(TROLL_CAVE_DIR + "obj/bones", random(2) + 1);
    add_npc(TROLL_CAVE_DIR + "npc/troll");
    add_npc(TROLL_CAVE_DIR + "npc/gtroll");
}
