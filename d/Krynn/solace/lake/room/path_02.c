/*
 * Outside room for the path to the Toron minotaur village
 * By Cherek Jan 2007. Made to inherit village_base_out.
 */

#include "../local.h"

inherit VILLAGE_BASE_OUT;

void
create_toron_room()
{
    set_location("PATH");
    set_short("Small track");
    set_start_desc("You are walking on a small track not far from " + 
                   "Crystalmir Lake. ");
    set_long_desc("Just to your north lies a newly built village. " +
                  "The track leads south towards the lake. ");

    add_village();
    add_structure();   
    add_path_items();
    
   

    add_exit(ROOM + "village_ent","north",0,3);
    add_exit(ROOM + "path_01","south",0,3);

    reset_room();
}
