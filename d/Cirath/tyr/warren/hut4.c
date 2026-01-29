/* Hut4: Hutess genericus. */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

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
    ::create_room();
    set_short("crumbling tenament");
    set_long ("This miserable excuse for a building is being used by a "+
              "several poor families as a shelter. If the rats don't get "+
              "them the easy spread of illness in such an environment "+
              "surely will.\n");

    INSIDE

    add_exit(TYR_WARREN+"rd_vr_03.c", "west", 0, 1);
    add_exit(TYR_WARREN+"rd_vr_02.c", "south", 0, 1);

    reset_room();
}
