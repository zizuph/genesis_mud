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
        "covers the sloping hills in every direction. You are on the " +
        "eastern edge of a deep valley, carved out from the powerful waters " +
        "of the great Anduin river as it flows down from the high mountains " +
        "in the north to empty out into the sea far to the south. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the east, an endless forest " +
        "of tall, black oak trees loom menacingly, waiting for you. " +
        "This is clearly the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger.\n");

    add_exit(VALE_DIR + "valen13w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen13w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen14w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen15w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen15w7", "north",0,2,1);
}
