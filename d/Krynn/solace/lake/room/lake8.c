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
    set_long_desc("The track leads north towards the mountains and " +
                  "southeast towards the lakeshore. You can hear " +
                  "noises coming from a small camp to the east " +
                  "and a path leads west entering a small clearing.");

    add_path_items();

    add_item("camp",
             "You cannot see who inhabits the site from here. \n");
        
    add_item("clearing",
             "It looks like the trees have been chopped down to " +
             "create the clearing. \n");
               
    add_item(({"mountain", "mountains"}),
               "You can spot snow on the top of the mountains. \n");               

    add_exit(ROOM + "path_01","north",0,3);
    add_exit(ROOM + "lake7","southeast",0,3);
    add_exit(ROOM + "campfire","east",0,3);
    add_exit(ROOM + "lake11","west",0,3);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "lake","lakeshore","water" }), 4);

    reset_room();

}
