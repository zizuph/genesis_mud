#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the north part of the city of "+
    "Drakmere, where the residential area is. The road runs east and "+
    "west along the north city wall. Right off to your east is a T "+
    "intersection. A small wooden house stands to your south.\n");
    add_item(({"city wall","wall"}),"The great wall that protects the "+
    "city from the savages that lie outside. Guards patrol the tops, "+
    "keeping an eye out for trouble.\n");
    add_item("house","Probably owned by residents of Drakmere.\n");
    add_exit(DRAKMERE_DIR + "road29","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road01","east",0,0,0);
    add_exit(DRAKMERE_DIR + "house03","south","@@house",0,0);
    
    add_npc(DRAKMERE_NPC_DIR + "dguard", 2);
}

int
house()
{
    write("You step quietly into the house.\n");
    return 0;
}


