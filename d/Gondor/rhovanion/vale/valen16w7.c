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
    set_herbs_8();
    
    set_short("Vale of the Anduin");
    set_long("You are completely surrounded by the tall green grass which " +
        "covers the ground here in every direction. You are on the " +
        "eastern side of a rocky valley, carved out from the strong waters " +
        "of the great Anduin river as it flows out of rugged mountains " +
        "in the north and running south towards the sea. On the " +
        "other side of the valley, tumbling foothills jump higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "and mighty Misty Mountains. To the east, a massive forest of " +
        "tall, black oak trees stand guard over the edge of the vale. " +
        "This can only be Mirkwood, the source of many terrifying legends " +
        "and tales.\n");

    add_exit(VALE_DIR + "valen15w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen15w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen16w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen17w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen17w7", "north",0,2,1);
}
