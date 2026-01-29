/* Hut2: Hutess genericus. */

inherit "/std/room";
#include "defs.h"

void reset_room()
{
    object npc=present("citizen", TO);
    if (!objectp(npc))
    {
        npc=clone_object (TYR_NPC+"poor_hmn");
        npc->arm_me();
        npc->move_living("into the room", TO);
    }
}

void create_room()
{
    set_short("small hut");
    set_long ("You find yourself inside a hut, with only spartan "+
              "furniture: A small table and some rugs to sleep on.\n");

    add_item(({"small table","table"}), "This small wood table looks as "+
               "if it would break if you put something on it.\n");
    add_item(({"rugs", "rug"}), "These rugs are put here to provide a "+
               "soft place to sleep.\n");

    INSIDE

    add_exit(TYR_WARREN+"rd_cw_06.c", "north", 0, 1);

    reset_room();
}
