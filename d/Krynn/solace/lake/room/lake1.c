/*
 * Outside room for the path to the Toron minotaur village
 * By Cherek Jan 2007. Made to inherit village_base_out.
 *
 * Added herbs, Arman 2017
 */

#include "../local.h"

inherit VILLAGE_BASE_OUT;
inherit "/d/Krynn/std/herbsearch";

string *herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );

void
create_toron_room()
{

    set_location("PATH");
    set_short("Lakeside track");
    set_start_desc("You are walking on a small track that follows " +
                   "alongside Crystalmir Lake. ");
    set_long_desc("The track leads south towards an intersection and " +
                  "north following the lakeshore. ");   
    	   	 
    add_path_items();

    add_item("intersection",
             "This narrow track seem to intersect with a larger road. \n");
 
    add_item("road",
             "The road to the south looks fairly wide and well-traveled. \n");
               
    add_exit(ROOM + "lake2","north",0,3);
    add_exit(CONNECT + "west_road7.c","south",0,3);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "lake","lakeshore","water" }), 4);

    reset_room();
}

