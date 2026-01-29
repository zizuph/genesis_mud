inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */


void
create_room()
{
    set_short("In the kitchen");
    set_long("You now stand in a room filled with good smells. "+
    "There are many burning fires, over which pots are placed. The "+
    "tables scattered around the room are covered with meats, "+
    "vegetables and fruits. The ground is covered with scraps of "+
    "food of all sorts. A few sacks of flour and barrels of "+
    "wine are stacked against a wall.\n");
  
    add_item("pots","Large iron pots filled with boiling water.\n");
    add_item("fires","The fires are hot, and servents are attending "+
    "them.\n");
    add_item("servents","They run around the room, chasing rats away "+
    "and checking on the food.\n");
    add_item("tables","The tables are made of plain wood, but are "+
    "covered with splatterd fruits, fish, beef, chicken, and all "+
    "sorts of other stuff.\n");
    add_item("ground","You see little rats scurrying around, nibbling "+
    "at left over food.\n");
    add_item("flour","Huge sacks of flour.\n");
    add_item("barrels","Very good vintage!\n");
    INSIDE;

    add_exit(NOBLE(alexander/m8),"north",0,-1,0);
    add_exit(NOBLE(alexander/m11),"east",0,-1,0);
    add_exit(NOBLE(alexander/m10),"south",0,-1,0);
    add_exit(NOBLE(alexander/m5),"west",0,-1,0);
}
