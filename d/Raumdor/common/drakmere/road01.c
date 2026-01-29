#include "defs.h"
inherit ROAD_ROOM;

/* By Sarr */

object guard;
object cap;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the north part of the city of "+
    "Drakmere, where the residential area of the city is. "+
    "The road ends here at the great wall, and splits off to the east "+
    "and west, while the rest of the city lies to the south.\n");
    add_item(({"great wall","wall"}),"The great wall that protects the "+
    "city from the savages that lie outside. Guards patrol the tops, "+
    "keeping an eye out for trouble.\n");
    reset_room();
    
   /* add_exit("/d/Raumdor/easter/room/p1105", "north");
    */
    add_exit(DRAKMERE_DIR + "road02","south",0,0,0);
    add_exit(DRAKMERE_DIR + "road30","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road31","east",0,0,0);    
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(DRAKMERE_NPC_DIR + "dguard");

        guard->move_living("xxx",TO);
    }
    if(!cap)
    {
        cap = clone_object(DRAKMERE_NPC_DIR + "dguard_cap");

        cap->move_living("xxx",TO);
    }

}


