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
    set_long_desc("The track leads north-southeast following the " +
                  "lakeshore. There is a break in the trees to the " +
                  "southwest where you can spot an old rotten dock. ");

    add_path_items();

    add_item(({"old rotten dock", "rotten dock", "dock", "old dock"}),
               "It seems unused and ready to break any second. \n");

    add_item("break",
             "Some trees have been removed to provide an entrance to " +
             "the dock. \n");
               
    add_exit(ROOM + "lake7","north",0,3);
    add_exit(ROOM + "lake5","southeast",0,3);
    add_exit(ROOM + "dock","southwest",0,3);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "lake","lakeshore","water" }), 4);

    reset_room();
}
