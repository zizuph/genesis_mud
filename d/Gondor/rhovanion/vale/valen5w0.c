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
    set_items_mirk();
    set_herbs_7();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellow-green grass surrounds you, bending and swaying" +
        "along with every faint breeeze which twists past you. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Directly to the west, you " +
        "can see the valley dive down to the edge of the Anduin, the great " +
        "river which flows down south past Gondor and into the sea. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To both the south and east, an " +
        "endless forest shrouded in shadow and gloom reaches out across " +
        "the horizon. This is Mirkwood, whose very name has been the " +
        "subject of many terrifying tales.\n");
    
    add_forest_entrance(MIRK_C_DIR + "r03/f07", "south");
    add_forest_entrance(MIRK_C_DIR + "r03/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r04/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r05/f08", "northeast");
    add_exit(VALE_DIR + "valen6w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen6w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen5w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen4w1", "southwest",0,2,1); 
}
