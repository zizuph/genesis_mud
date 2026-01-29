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
    set_start_desc("You are walking on a narrow dirt road within " +
                   "a small village. ");
    set_long_desc("The road leads north-south. East lies the entrance " +
                  "to a rather poorly constructed hut. "); 

    add_road_items(); 
    add_fires();
    add_smoke();
    add_hut();
    add_trees();
    add_path();
    add_village();
    add_lake();
    add_structure();
    add_hides();
    add_dirt_mud();
    add_poles_logs();
    add_pots();
    add_hut_entrance();
    
    add_exit(ROOM + "village_j","north",0,3);
    add_exit(ROOM + "village_h","south",0,3);    
    add_exit(ROOM + "village_hut_03","east",0,3);

    reset_room();
}
