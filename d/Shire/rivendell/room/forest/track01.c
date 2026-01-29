/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
#include <macros.h>
 
inherit FOREST_BASE;

object ranger;

void
create_forest_room()
{
 
    set_vbfc_extra(forest_desc3);
    if(check_person)
    {
        add_my_desc("A white stone lays buried beneath some moss and leaves.\n");
    }
/*    
    add_item("white stone",
        "Moss and heather grow over it, concealing it from the " +
        "casual tracker. It has a star engraved on the upper " +
        "right-hand corner.\n");
    add_item("moss",
        "It is a verdant green color, looking velvet in the " +
        "dappled light. The moss grows over and across the " +
        "stones, covering them in a blanket of green.\n");
    add_item("heather",
        "The heather is a rich green color with tiny pink " +
        "bell-shaped flowers. The plant is covered with tiny " +
        "leaves and crawls all over the floor of the forest.\n");
*/
    set_add_white_stone("upper right-hand corner", "upper center");
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


void reset_shire_room()
{
    if (!objectp(ranger))
    {
	ranger = clone_object(RANGER_NPC+"n_ranger");
	ranger->arm_me();
	ranger->add_prop(OBJ_I_HIDE, 50);
	ranger->move(TO);
    }
}