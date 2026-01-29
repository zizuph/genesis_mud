/*
 * Outside room in the Toron minotaur village
 * By Cherek Jan 2007. Made to inherit village_base_out.
 */

#include "../local.h"

inherit VILLAGE_BASE_OUT;

object mino1, mino2;

void
reset_toron_room()
{
    if (!objectp(mino1))
    {
        mino1=clone_object(NPC + "minotaur_standard.c");
        mino1->move(TO, 1);
    }
    
    if (!objectp(mino2))
    {
        mino2=clone_object(NPC + "minotaur_standard.c");
        mino2->move(TO, 1);
    }
}

void
create_toron_room() 
{

    set_location("ROAD");
    set_short("Village Entrance");
    set_start_desc("Before you stands the entrance to a rather small " +
                   "village consisting of mostly tents and simple " +
                   "wooden huts. ");
    set_long_desc("A dirt road leads north towards an intersection and " +
                  "a small path leads southwards. ");

    add_item("intersection",
             "Two roads seem to intersect, one leading east-west and " +
             "another wider road leading north-south. \n");

    add_road_items(); 
    add_fires();
    add_smoke();
    add_trees(); 
    add_path();
    add_village();
    add_lake();
    add_structure();
    add_hides();
    add_dirt_mud();
    add_poles_logs();
    add_pots();
    add_entrance();

    add_exit(ROOM + "village_01","north",0,3);
    add_exit(ROOM + "path_02","south",0,3);

    reset_room();
}


