/*
 * entrance.c
 *
 * Entance to the Troll cave.  
 * 
 * Lucius - Jan 2021
 *    Modernized.
 *
 * Lilith - Jan 2022: Connected to moor area that was moved 
 *             out of Sorgum's dir and modernized.
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
    set_short("cave entrance");
    set_long(query_long() +
        "You may return down towards the swamp or head north into" +
        " the dark cave before you.\n");

    add_exit(TROLL_CAVE_DIR + "tcave01",   "north");
    add_exit(MOOR_DIR + "main/cliff", "down");
}
