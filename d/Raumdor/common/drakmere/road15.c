#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are now in the westernmost part of the city center. "+
    "Off to the east is the city square, where a large fountain sits "+
    "in the center. Various shops and inns surround the square. The "+
    "ground is still dirt, but as you progress further east, it turns "+
    "to cobble stone, which is what the majority of the city square "+
    "is made of. To the north you see a little building with a blue "+
    "sign over it, to the south you see a large stone building with "+
    "a white sign over it, while to the west, the road leads back "+
    "to the city gates.\n");
    add_item(({"fountain"}),"From this distance, it looks like a "+
    "circle of stone with a pole sticking out spouting water.\n");
    add_item(({"sign","signs"}),"Which one? The blue or white?\n");
    add_item(({"blue sign"}),"It reads: Post Office.\n");
    add_item(({"white sign"}),"It reads: Bank of Drakmere.\n");
    add_exit(DRAKMERE_DIR + "road16","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road14","west",0,0,0);
    add_exit(DRAKMERE_DIR + "shop/d_po","north",0);
    add_exit(DRAKMERE_DIR + "shop/d_bank","south",0);
    
    add_npc(DRAKMERE_NPC_DIR + "dguard", 2);
}
