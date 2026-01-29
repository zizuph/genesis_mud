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
    set_long("There is tall, yellow grass surrounding you here, waving in " +
        "the breeze as it covers the sloping hills in every direction. You " +
        "at the bottom of a deep valley, carved out from the powerful waters " +
        "of the great Anduin river as it flows down from the high mountains " +
        "in the north to empty out into the sea far to the south. To the " +
        "west, on the other side of the valley, rugged foothills march high " +
        "into the air, seemingly touching the heavens as they grow into the "+
        "magestic Misty Mountains of legend. To the northeast, endless lines " +
        "of tall, black oak trees loom menacingly immediately before you. " +
        "This is clearly the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger.\n");

    add_exit(VALE_DIR + "valen16w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen16w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen17w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen18w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen18w7", "north",0,2,1);
}
