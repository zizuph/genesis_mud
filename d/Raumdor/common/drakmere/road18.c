#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are now in the easternmost part of the city center. "+
    "Off to the west is the city square, where a large fountain sits "+
    "in the center. Various shops and inns surround the square. The "+
    "ground is still dirt, but as you progress further west, it turns "+
    "to cobble stone, which is what the majority of the city square "+
    "is made of. To the north you see a stone-wood building with a gold "+
    "sign over it, to the south you see a stone building with "+
    "a silver sign over it, while to the east, the road goes on.\n");
    add_item(({"fountain"}),"From this distance, it looks like a "+
    "circle of stone with a pole sticking out spouting water.\n");
    add_item(({"sign","signs"}),"Which one? The gold or silver?\n");
    add_item(({"gold sign"}),"It reads: Equipment Store.\n");
    add_item(({"silver sign"}),"It reads: General Store.\n");
    add_exit(DRAKMERE_DIR + "road19","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road17","west",0,0,0);
    add_exit(DRAKMERE_DIR + "shop/eshop","north",0);
    add_exit(DRAKMERE_DIR + "shop/gshop","south",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard", 2);
}
