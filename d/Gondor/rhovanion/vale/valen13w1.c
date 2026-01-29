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
    set_herbs_4();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellowish grass surrounds you, swaying and brushing " +
        "against your legs with every faint breeeze which blows by. You are " +
        "on the eastern side of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Directly to the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the east, the endless forest of tall, " +
        "black oak trees which loom menacingly is known as the mighty " +
        "Mirkwood Forest. There are many tales of Mirkwood, all of which " +
        "tell of the darkness and danger found within.\n");

    add_exit(VALE_DIR + "valen12w1", "south",0,2,1);
    add_exit(VALE_DIR + "valen12w0", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen13w0", "east",0,2,1);
    add_exit(VALE_DIR + "valen14w0", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen14w1", "north",0,2,1);
    add_exit(VALE_DIR + "valen14w2", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen13w2", "west",0,2,1);
    add_exit(VALE_DIR + "valen12w2", "southwest",0,2,1); 
}
