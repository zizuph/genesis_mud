/* By Sarr */
#include "defs.h"
inherit ROAD_ROOM;

object gilbert;

void
create_room()
{
    ::create_room();
    set_short("In the city square");
    set_long("You are now in the west part of the city square. The "+
    "ground is made of cobble stone. In the center, just off to your "+
    "east, is a large fountain. Various shops surround this square, "+
    "and people are trudging slowly through another grim day in "+
    "Raumdor. To the west is the road to the city gates, while to "+
    "the east is the rest of the city square. There is a little "+
    "stone building to the northwest with a blue sign over it, "+
    "while to the southwest, a large stone building sits with a "+
    "white sign over it.\n");
    add_item(({"fountain"}),"From this distance, it looks like a "+
    "circle of stone with a pole sticking out spouting water.\n");
    add_item(({"sign","signs"}),"Which one? The blue or white?\n");
    add_item(({"blue sign"}),"It reads: Post Office.\n");
    add_item(({"white sign"}),"It reads: Bank of Drakmere.\n");
    add_exit(DRAKMERE_DIR + "road06","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road15","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road05","northeast",0,0,0);
    add_exit(DRAKMERE_DIR + "road07","southeast",0,0,0);
    add_exit(DRAKMERE_DIR + "shop/d_po","northwest",0);
    add_exit(DRAKMERE_DIR + "shop/d_bank","southwest",0);
    
    seteuid(getuid(this_object())); 
        
    reset_room();
}


void
reset_room()
{	
    if (!gilbert)
    {        	
        gilbert = clone_object(DRAKMERE_NPC_DIR + "gilbert");
        gilbert->move_living("xxx",TO);                
    }    
}
