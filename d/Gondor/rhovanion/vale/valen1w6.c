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
    set_items_oldroad();
    set_herbs_5();
    
    set_short("Vale of the Anduin");
    set_long("You are on the eastern slopes of the vale of the Anduin, " +
        "surrounded by a field of tall, yellowish grasses which bend and " +
        "sway in the gentle breeze. Through the middle of the valley, " +
        "the great river rushes by as the powerful waters wander on their " +
        "journey south towards Gondor and the sea. On the far side of the " +
        "valley, rocky foothills transform themselves into the rugged " +
        "face of the Misty Mountains, whose stony peaks touch the very sky. " +
        "Sprawled across the entire eastern horizon, dark and shadowy " +
        "woods line the edge of the vale. Oak trees tall and black announce " +
        "the boundary of the legendary Mirkwood forest. Not far to the south, " +
        "you see what appears to be an old road, cutting across the vale, " +
        "connecting the forest to a wide ford which crosses the river.\n");

    add_exit("/d/Shire/anduin/east/rd01", "south",0,2,1);
    add_exit("/d/Shire/anduin/east/rd02", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen1w5", "east",0,2,1);
    add_exit(VALE_DIR + "valen2w5", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen2w6", "north",0,2,1);
    add_exit(VALE_DIR + "valen2w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen1w7", "west",0,2,1);
    add_exit("/d/Shire/anduin/east/eford", "southwest",0,2,1);   
}
