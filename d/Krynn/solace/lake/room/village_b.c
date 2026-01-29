/*
 * Outside room in the Toron minotaur village
 * By Cherek Jan 2007. Made to inherit village_base_out.
 */
 
#include "../local.h"

inherit VILLAGE_BASE_OUT;

object mino1;

void
reset_toron_room()
{
    if (!objectp(mino1))
    {
        mino1 = clone_object(NPC + "minotaur_standard.c");
        
        mino1->move(TO, 1);
        
        tell_room(TO, "A minotaur arrives.\n", mino1);
    }
}

void
create_toron_room()
{
    set_location("ROAD");
    set_short("On a dirt road");
    set_start_desc("You are walking on a narrow dirt road within " +
                   "a small village. ");
    set_long_desc("The road leads north deeper inside the village " +
                  "and east towards an intersection. Southwest lies " +
                  "the entrance to a rather large tent. ");

    add_item("intersection",
             "Two roads seem to intersect, one leading east-west and " +
             "another wider road leading north-south. \n");

    add_road_items(); 
    add_fires();
    add_smoke(); 
    add_tent();
    add_trees(); 
    add_path();
    add_village();
    add_lake();
    add_structure(); 
    add_tent_entrance();
    add_hides();
    add_dirt_mud();    

    add_exit(ROOM + "village_c","east",0,3);
    add_exit(ROOM + "village_a","north",0,3);
    add_exit(ROOM + "village_tent_01","southwest",0,3);

    reset_room();
}


