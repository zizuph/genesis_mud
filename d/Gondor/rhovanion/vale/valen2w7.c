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
    set_herbs_3();
    
    set_short("Vale of the Anduin");
    set_long("A tall yellow-green grass encompasses the world around you, " +
        "coveringthe sloping hills in every direction. You are currently at " +
        "the bottom of a deep valley, carved out from the powerful waters " +
        "of the great Anduin river as it flows down from the high mountains " +
        "in the north to empty out into the sea far to the south. On the " +
        "west side of the valley, rocky foothills stretch higher and " +
        "higher until they pierce the clouds above as the majestic " +
        "Misty Mountains of legend. To the east, an endless forest " +
        "of tall, black oak trees loom menacingly along the edge of the " +
        "valley. This is the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger.\n");

    add_exit(VALE_DIR + "valen1w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen1w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen2w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen3w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen3w7", "north",0,2,1);
}
