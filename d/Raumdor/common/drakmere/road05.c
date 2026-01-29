#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

object guard;

void reset_room();

void
create_room()
{
    ::create_room();
    set_short("In the city square");
    set_long("You are now in the north part of the city square. The "+
    "ground is made of cobble stone. In the center, just off to your "+
    "south, is a large fountain. Various shops surround this square, "+
    "and people are trudging slowly through another grim day in "+
    "Raumdor. To the north is the road into the residential area, while "+
    "to the south is the rest of the city square.\n");
    add_item(({"fountain"}),"From this distance, it looks like a "+
    "circle of stone with a pole sticking out spouting water.\n");
    reset_room();
    add_exit(DRAKMERE_DIR + "road04","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road06","south",0,0,0);
    add_exit("/d/Raumdor/guilds/lc/room/join", "east");
    add_exit(DRAKMERE_DIR + "road16","southwest",0,0,0);
    add_exit(DRAKMERE_DIR + "road17","southeast",0,0,0);
}


void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(DRAKMERE_NPC_DIR + "dguard");

        guard->move_living("xxx",TO);
    }
}

