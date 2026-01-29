#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the west part of the city of "+
    "Drakmere. The westgate lies to the west of you, while the main "+
    "plaza and heart of the city lies to the east. Another dirt road "+
    "leads up north. You can see the large keep rising up in the south.\n");
    add_item(({"keep"}),"Where the royalty live. Its strong walls probably "+
    "house the Lord of Drakmere himself.\n");
    add_exit(DRAKMERE_DIR + "road14","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road12","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road23","north",0,0,0);
}
