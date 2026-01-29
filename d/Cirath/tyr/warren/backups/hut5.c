/* Hut5: Hutess genericus. */

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
    set_short("old wooden shanty");
    set_long ("The walls of this structure are made of wood, but that is "+
              "no sign of wealth, as it all is warped and rotten. That "+
              "it doesn't collapse on your head is a small miracle.\n");

    INSIDE

    add_exit(TYR_WARREN+"rd_vr_03.c", "south", 0, 1);

    reset_room();
}
