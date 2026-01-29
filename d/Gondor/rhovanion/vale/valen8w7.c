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
    set_items_carrock();
    set_herbs_6();
    
    set_short("Vale of the Anduin");
    set_long("A tall, green grass surrounds you, swaying and brushing " +
        "against you with every faint breeze which twists past. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. In the middle of the " +
        "river, a massive stone island rises up through the water. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the east, the endless forest of tall, " +
        "black oak trees which loom menacingly is known as the mighty " +
        "Mirkwood Forest. There are many tales of Mirkwood, all of which " +
        "tell of the darkness and danger found within.\n");

    add_exit(VALE_DIR + "valen7w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen7w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen8w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen9w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen9w7", "north",0,2,1);
    add_exit(VALE_DIR + "cave1", "west", "@@path@@", 2,1);
}
int
path()
{
write("You carefully make your way across the path of flat stones " +
    "to stand outside a cave in the side of the massive rock.\n");
return 0;
}