#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("In the courtyard of the Keep of Drakmere");
    set_long("You are now in a lovely courtyard outside the Keep of "+
    "Drakmere. The Keep looks old and worn. The stones are blackened "+
    "in some spots. Windows dot the wall all around. At each four "+
    "corners you see a short tower, with guards standing. The area "+
    "around you is covered with flowers of all types. The air smells "+
    "sweet and lovely. Despite the grim atmoshpere common to Raumdor, "+
    "you feel a bit cheerful walking through here.\n");
    add_item("flowers","Green, yellow, blue, violet, red flowers dot the "+
    "landscape, adding colorful joy to the atmosphere.\n");
    add_item("keep","Its just to the west of here.\n");
    add_item(({"tower","towers"}),"They are short and have guards standing "+
    "around them.\n");
    add_item("stones","They look ancient.\n");
    add_exit(DRAKMERE_DIR + "road49","west");
    add_exit(DRAKMERE_DIR + "road10","east");
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard", 4);
}
