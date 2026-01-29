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
    set_long_desc("The road ends here at the entrance to a rather poorly " +
                  "constructed hut. Looking south you see nothing but more " +
                  "tents and huts. "); 

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
    
    add_exit(ROOM + "village_hut_02","northeast",0,3);
    add_exit(ROOM + "village_i","south",0,3);

    reset_room();
}
