/*
 * Vale of the Anduin.
 * Varian 2015
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "vale/base";

void 
create_vale_room()
{
    set_items_vale();
    set_items_east();
    set_items_river();
    set_herbs_9();
    
    set_short("Vale of the Anduin");
    set_long("You are standing at the bottom of a deep valley, on the east " +
        "bank of the Anduin river, surrounded by a tall, yellow grass which " +
        "sways back and forth in the breeze. The river is wide and powerful, " +
        "cutting deep into the land as it tumbles down from the mountains " +
        "in the north and rushing towards the sea in the south. Rocky " +
        "foothills on the west side of the valley march upwards into the " +
        "treacherous heights of the Misty Mountains which claw into the " +
        "cloudy sky above. Lying in wait upon the eastern rim of the vale, " +
        "endless rows of tall, black trees loom menacingly. This is the " +
        "legendary Mirkwood forest, the dark subject of many terrifying " +
        "tales.\n");

    add_exit(VALE_DIR + "valen4w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen4w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen5w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen6w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen6w7", "north",0,2,1);
}
