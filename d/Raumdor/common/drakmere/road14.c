/* By Sarr */
#include "defs.h"
inherit ROAD_ROOM;

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the west part of the city of "+
    "Drakmere. You are close now to the city center just off to the east. "+
    "The gates are to the west, while you see a large keep rising over "+
    "the houses to the southwest.\n");
    add_item(({"keep"}),"Where the royalty live. Its strong walls probably "+
    "house the Lord of Drakmere himself.\n");
    clone_object(DRAKMERE_DIR + "mhdoor1")->move(TO);
    add_exit(DRAKMERE_DIR + "archives","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road15","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road13","west",0,0,0);
}
