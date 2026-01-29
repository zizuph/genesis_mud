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
    set_long_desc("To the north you notice a rather newly built " +
                  "village while the track leads south towards the lake. ");
    
     add_item("village",
              "The village looks quite large, but it is hard to tell " +
              "this far away. \n");

    add_path_items();

    add_exit(ROOM + "path_02","north",0,3);
    add_exit(ROOM + "lake8","south",0,3);

    reset_room();
}

