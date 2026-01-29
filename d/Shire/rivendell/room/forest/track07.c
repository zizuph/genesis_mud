/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
 
void
create_forest_room()
{
     set_vbfc_extra(forest_desc2);
 
     if(check_person)
    {
        add_my_desc("A white stone lays hidden in the leaves.\n");
    }

    set_add_white_stone("upper right-hand corner", "lower left-hand edge");

    add_item("white stone",
        "An unusual white stone lies hidden in the bushes,  " +
        "unlikely to be detected save by trained eyes. A star " +
        "is engraved on the right hand side of the stone. A moon " +
        "is engraved on the lower left-hand side of the stone.\n");
    add_item("moss",
        "It is a verdant green color, looking velvet in the " +
        "dappled light. The moss grows over and across the " +
        "stones, covering them in a blanket of green.\n");
    add_item("heather",
        "The heather is a rich green color with tiny light green " +
        "bell-shaped flowers. The plant is covered with tiny " +
        "leaves and crawls all over the floor of the forest.\n");
    add_item(({"stones", "rocks"}),
        "Various rocks and stones are buried under the leaves. They " +
        "look like they have been washed down from the " +
        "mountains and are of various colors.\n");
    add_item(({"colored stones", "colored rocks"}),
        "You see some red, gray, black, white, and other " +
        "colored stones scattered about.\n");
    add_item(({"black stones", "black rocks", "red stones", "red rocks", 
            "white stones", "white rocks", "gray stones", 
            "gray rocks"}),
        "The stones are scattered about, some buried under the " +
        "leaves and forest debris.\n");

    reset_shire_room();
    add_forest_herbs();
    add_exit(FOREST_DIR + "forest17", "south",0,4, check_player(3));
    add_exit(FOREST_DIR + "plateau", "east", 0,4, check_player(0));
    add_exit(FOREST_DIR + "track06", "southwest", 0,4, check_player(0));

}

void reset_shire_room()
{
    set_searched(0);

}
