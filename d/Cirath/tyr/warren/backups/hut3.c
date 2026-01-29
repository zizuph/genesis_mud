/* Hut3: Searching the beds will reveal something here. */

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
    set_short("poor hovel");
    set_long ("While remarkably clean for a home so close to the slums, the "+
              "hovel is still somewhat lacking the usual amenities. "+
              "Piles of rags used as beds and an old uneven slab used "+
              "as a table can just barely be considered livable.\n");

    add_item(({"piles", "pile", "rags", "rag", "bed", "beds"}),
             ("Calling this a bed is a strong complement, but it is "+
              "probably more comfortable then the uncovered floor.\n"));

    add_item(({"slab", "table"}),
             ("Made of the same material as Kalak's ziggurat, this was "+
              "likely discarded for some real or imagined imperfection.\n"));

    INSIDE

    add_exit(TYR_WARREN+"rd_vr_01.c", "south", 0, 1);

    reset_room();
}
