/* By Sarr */
#include "defs.h"
inherit ROAD_ROOM;


void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long(
      "You are on a dirt road in the east part of the city of Drakmere, " +
      "where the residential area is. You now stand at the place where the " +
      "east and south walls meet. The road leads up north along the east " +
      "wall, and west along the south wall. There is a small hut against the " +
      "wall here.\n");
    add_item(({"city wall", "wall"}),
      "The great wall that protects the city from the savages that lie " +
      "outside. Guards patrol the tops, keeping an eye out for trouble.\n");
    add_item("hut",
      "The hut is made of straw, and looks rather small and decrepid.\n");
    add_cmd_item("hut", "enter", "@@enter_hut@@");
    add_exit(DRAKMERE_DIR + "road42", "north", 0, 0);
    add_exit(DRAKMERE_DIR + "road44", "west", 0, 0);
    
    add_npc(DRAKMERE_NPC_DIR + "dguard", 2);
    
    reset_room();
}

string
enter_hut()
{
    TP->move_living("in", DRAKMERE_DIR + "wise_hut");
    return "";
}

void
reset_room()
{
}
