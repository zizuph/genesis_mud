/*
 * cave08.c
 *
 * A cave room.
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
        "Some furs and a pile of bones lay on the ground. This room looks " +
        "like something made its home here.\n");

    DARK;

    add_item(("furs"),"Various woodland creatures mostly. Used as bedding.\n");
    add_item(("bones"),"Various sized bones. Some look large enough to be " +
       "humanoid in origin.\n");

    add_cmd_item("sign", "read",
        "\"Property of the Terel orc family.\"\n");

    add_exit(MOUNTAIN_DIR + "goblincave/cave07", "southwest");
    add_exit(MOUNTAIN_DIR + "goblincave/cave09", "north");
    add_exit(MOUNTAIN_DIR + "goblincave/cave12", "southeast");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin", 2);
}
