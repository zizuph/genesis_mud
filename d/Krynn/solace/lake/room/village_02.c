/*
 * Outside room in the Toron minotaur village
 * By Cherek Jan 2007. Made to inherit village_base_out.
 */
 
#include "../local.h"

inherit VILLAGE_BASE_OUT;

void
create_toron_room()
{

    set_location("ROAD");
    set_short("On a dirt road");
    set_start_desc("You are walking on a narrow dirt road within a " +
                   "small village. ");
    set_long_desc("The road leads north towards a wooden structure " +
                  "and south to an intersection. ");   

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
    add_dirt_mud();
    add_poles_logs();
    add_pots();
    
    add_exit(ROOM + "village_03","north",0,3);
    add_exit(ROOM + "village_01","south",0,3);

    reset_room();
}

