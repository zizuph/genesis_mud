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
    set_items_mirk();
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("You are completely surrounded by the tall yellow grass which " +
        "covers the sloping hills in every direction. You are on the " +
        "eastern edge of a deep valley, carved out from the powerful waters " +
        "of the great Anduin river as it flows down from the high mountains " +
        "in the north to empty out into the sea far to the south. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the northeast, an endless forest " +
        "of tall, black oak trees looms menacingly immediately before you. " +
        "This is clearly the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger.\n");

    add_exit(VALE_DIR + "valen17w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen17w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen18w6", "east",0,2,1);
    add_exit(MIRK_EP_DIR + "p01", "northeast","@@gate@@", 2,1);
    add_exit(VALE_DIR + "valen19w7", "north",0,2,1);
}

int
gate()
{
write("The forest is so thick here that you cannot find an entrance, " +
    "however, there does appear to be a path leading directly into the " +
    "forest gate just north of here.\n");
return 1;
}
