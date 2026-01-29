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
 
    set_vbfc_extra(forest_desc);
 
    add_item("white stone",
        "Moss and heather grow over it, concealing it from the " +
        "casual tracker.\n");
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
