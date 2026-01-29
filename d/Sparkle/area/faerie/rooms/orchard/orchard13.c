/*
 * /d/Sparkle/area/faerie/rooms/orchard/orchard13.c
 *
 * The orchard of Faerie
 * By Finwe, September 1999
 */
 
#include "defs.h"
 
inherit ORCHARD_BASE;

object dogcow;

void add_npcs();

void
create_orchard_room()
{
    //add_my_desc("\n");
    add_exit(ORCHARD_DIR + "orchard06", "north");     
    add_exit(ORCHARD_DIR + "orchard16", "south");
    add_exit(ORCHARD_DIR + "orchard14", "east");
    add_exit(ORCHARD_DIR + "orchard12", "west");

    add_std_herbs("forest");

    reset_room();
}

void reset_room()
{
    ::reset_room();
    add_npcs();
    set_searched(0);
    fruit_counter = 0;
}

void add_npcs()
{
   if(!objectp(dogcow))
    {
        dogcow = clone_object(NPC_DIR + "dogcow");
        dogcow->set_restrain_path(ORCHARD_DIR);
        dogcow->set_random_move(2);
        dogcow->move(TO);
    }
}
