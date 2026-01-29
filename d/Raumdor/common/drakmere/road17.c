#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("In the city square");
    set_long("You are now in the east part of the city square. The "+
    "ground is made of cobble stone. In the center, just off to your "+
    "west, is a large fountain. Various shops surround this square, "+
    "and people are trudging slowly through another grim day in "+
    "Raumdor. To the east is a road into more of the city, while to "+
    "the west is the rest of the city square. There is a wooden-"+
    "stone building to the northeast with a gold sign over it, "+
    "while to the southeast, a large wooden building sits with a "+
    "silver sign over it.\n");
    add_item(({"fountain"}),"From this distance, it looks like a "+
    "circle of stone with a pole sticking out spouting water.\n");
    add_item(({"sign","signs"}),"Which one? The gold or silver?\n");
    add_item(({"gold sign"}),"It reads: Equipment shop.\n");
    add_item(({"silver sign"}),"It reads: General store.\n");
    add_exit(DRAKMERE_DIR + "road18","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road06","west",0,0,0);
    add_exit(DRAKMERE_DIR + "shop/eshop","northeast",0);
    add_exit(DRAKMERE_DIR + "shop/gshop","southeast",0);
    add_exit(DRAKMERE_DIR + "road05","northwest",0,0,0);
    add_exit(DRAKMERE_DIR + "road07","southwest",0,0,0);
}
