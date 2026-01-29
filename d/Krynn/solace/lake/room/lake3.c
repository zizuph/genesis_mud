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
    set_long_desc("The track leads southeast-northwest following " +
                  "the lakeshore. To your northeast a path leads to " +
                  "a large stone structure in the distance.");

    add_path_items();
    add_item(({"structure","stone structure","large stone structure",
          "school of high magic","school","poolbottom"}),
          "In the distance stands a large stone structure, the School of " +
          "High Magic known as Poolbottom, where aspiring magi and apprentices " +
          "train in the magical Art prior to being considered for the Test of High Sorcery.\n");

    add_exit(ROOM + "lake4","northwest",0,3);
    add_exit(ROOM + "lake2","southeast",0,3);
    add_exit("/d/Krynn/solace/poolbottom/room/poolbottom_path1","northeast",0,3);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "lake","lakeshore","water" }), 4);

    reset_room();
}

int
school_closed()
{
    write("The School of High Magic is closed while Master Theobald "+
          "is in conclave at the Tower of Wayreth. It will open on his "+
          "return.\n");

    return 1;
}