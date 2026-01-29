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
    set_start_desc("You are walking on a small track near " + 
                   "Crystalmir Lake. ");
    set_long_desc("The track leads northwest towards the mountains " +
                  "and south following the lakeshore.");

    add_path_items();
    
    add_item(({"mountain", "mountains"}),
               "You can spot snow on the top of the mountains. \n");
               
    add_exit(ROOM + "lake8","northwest",0,3);
    add_exit(ROOM + "lake6","south",0,3);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "lake","lakeshore","water" }), 4);

    reset_room();
}

