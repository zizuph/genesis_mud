/* slum1: A place for the dregs of the earth to rob you. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
void reset_room()
{
    bring_room_mob ("akabarl", TYR_NPC+"slumlord.c", 1, 1);
    bring_room_mob ("dweller", TYR_NPC+"poor_mob.c", 1);
}

void create_room()
{
    set_short("central slums");
    set_long ("All around is the worst filth in all of Tyr: The vilest "+
              "citizens, the ugliest wooden shelters, and the accumulated "+
              "refuse of an entire city. The people here have a hunted look "+
              "in their eyes, as if they face some particular pain in this "+
              "foul place. Welcome to the center of Tyr's slums.\n");

    OUTSIDE
    ADD_SUN_ITEM;

    add_exit(TYR_WARREN+"rd_vr_01.c", "southwest", 0, 1);
    add_exit(TYR_WARREN+"slum4.c", "north", 0, 1);
    add_exit(TYR_WARREN+"slum3.c", "east", 0, 1);
    add_exit(TYR_WARREN+"slum2.c", "south", 0, 1);

    reset_room();
}
