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
    set_herbs_2();
    
    set_short("Vale of the Anduin");
    set_long("Standing on the banks of the great Anduin river, you are " +
        "surrounded by tall, yellow grasses which cover the deep valley " +
        "carved out by the river as it rumbles southwards to the sea. On the " +
        "other side of the valley, rugged hills and rocky outcroppings " +
        "claw upwards until they pierce the clouds above as the mighty " +
        "Misty Mountains of legend. Looming with malice and menace, tall " +
        "black trees line the eastern edge of the vale as they mark the " +
        "boundary of the infamous Mirkwood forest.\n");

    add_exit(VALE_DIR + "valen2w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen2w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen3w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen4w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen4w7", "north",0,2,1);
}
