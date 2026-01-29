#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the north part of the city of "+
    "Drakmere. You are close now to the city center just off to the south. "+
    "A small wooden house stands to your west and east.\n");
    add_item("house","Probably owned by residents of Drakmere.\n");
    add_exit(DRAKMERE_DIR + "road03","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road05","south",0,0,0);
    add_exit("/d/Raumdor/guilds/gc/room/join", "west");
    add_exit("/d/Raumdor/common/drakmere/felix/froom", "northeast");
}

int
house()
{
    write("You step quietly into the house.\n");
    return 0;
}


