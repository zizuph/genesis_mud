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
    set_long("You are now in the south part of the city square. The "+
    "ground is made of cobble stone. In the center, just off to your "+
    "north, is a large fountain. Various shops surround this square, "+
    "and people are trudging slowly through another grim day in "+
    "Raumdor. To the south is the road to the south gates, while "+
    "to the north is the rest of the city square. A small stone "+
    "building is off the the southwest, where you hear hammering "+
    "noises. And off the your southeast, you see a huge stone "+
    "structure with a red sign over the entrance.\n");
    add_item(({"red sign","sign"}),"It reads: Bloody Skull Inn.\n");
    add_item(({"fountain"}),"From this distance, it looks like a "+
    "circle of stone with a pole sticking out spouting water.\n");
    reset_room(); 
    add_exit(DRAKMERE_DIR + "road06","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road08","south",0,0,0);
    add_exit(DRAKMERE_DIR + "road16","northwest",0,0,0);
    add_exit(DRAKMERE_DIR + "road17","northeast",0,0,0);
    add_exit(DRAKMERE_DIR + "smith","southwest",0,0,0);
    add_exit(DRAKMERE_DIR + "shop/inn","southeast",0,0,0);
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

