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
    set_herbs_6();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellow-green grass surrounds you, swaying and bending " +
        "with every faint breeeze which twists and swirls past. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Directly to the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the east, the endless forest of tall, " +
        "black oak trees which loom menacingly is known as the mighty " +
        "Mirkwood Forest. There are many tales of Mirkwood, all of which " +
        "tell of the darkness and danger found within.\n");

    add_exit(VALE_DIR + "valen8w3", "south",0,2,1);
    add_exit(VALE_DIR + "valen8w2", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen9w2", "east",0,2,1);
    add_exit(VALE_DIR + "valen10w2", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen10w3", "north",0,2,1);
    add_exit(VALE_DIR + "valen10w4", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen9w4", "west",0,2,1);
    add_exit(VALE_DIR + "valen8w4", "southwest",0,2,1); 
}
