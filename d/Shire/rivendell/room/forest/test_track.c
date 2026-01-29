/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
#define MIN_AWARE 25

void
create_forest_room()
{
 
    set_vbfc_extra(forest_desc);
 
    add_item("white stone",
        "Moss and heather grow over it, concealing it from the " +
        "casual tracker. @@hide_track@@\n");
    add_item("moss",
        "It is a verdant green color, looking velvet in the " +
        "dappled light. The moss grows over and across the " +
        "stones, covering them in a blanket of green.\n");
    add_item("heather",
        "The heather is a rich green color with tiny pink " +
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
    add_prop("_obj_s_search_fun", "do_search");

    add_exit(FOREST_DIR + "forest38", "north", 0,4, check_person);
    add_exit(FOREST_DIR + "forest54", "south","@@bush_exit@@", 4, check_person);
    add_exit(FOREST_DIR + "forest45", "east", 0,4, check_person);
    add_exit(FOREST_DIR + "track02",  "northeast", 0,4, check_person);


}

int bush_exit()
{
    write ("You go south and crash through the bushes.\n");
    say(QCTNAME(TP) + " goes south and crashes through the bushes.\n");
    tell_room(FOREST_DIR + "forest54",
              QCTNAME(TP)+" comes crashing through the forest and startles you.\n",
              TP);


}

string hide_track()
{
    int awareness;

    awareness = TP->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE + random (MIN_AWARE)) return " ";
    return " It sits on the edge of a hidden track in the forest.";
}



string hide_stone(object searcher, string str)
{
    int awareness;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;

    if(!str || (str!= "white stone")) return 0;
    say(QCTNAME(searcher)+ " finds something in the forest's floor.\n");
    return "After brushing the mosses and debris away from the " +
        "white stone, you notice a star engraved on it. The " +
        "star points northeast.\n";
}

