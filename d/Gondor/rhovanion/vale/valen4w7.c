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
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("Tall, yellow grasses sway in the breeze, brushing against you " +
        "with every gust of wind. The grass fills the vale of the great " +
        "river Anduin, blanketing the rocky slopes of the valley and " +
        "following the path of the river as it tumbles southwards towards " +
        "the sea. Across the river, on the west side of the valley, rugged " +
        "foothills leap up towards the sky as they grow up into the Misty " +
        "Mountains. Far to the east, an endless line of tall, black trees " +
        "mark the boundary of the legendary Mirkwood, a forest which has " +
        "been the subject of many terrifying tales.\n");

    add_exit(VALE_DIR + "valen3w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen3w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen4w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen5w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen5w7", "north",0,2,1);
}
