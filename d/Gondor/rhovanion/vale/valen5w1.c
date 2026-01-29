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
    set_herbs_5();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellowish grass surrounds you, bending and swaying" +
        "along with every faint breeeze which twists past you. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Directly to the west, you " +
        "can see the valley dive down to the edge of the Anduin, the great " +
        "river which flows down south past Gondor and into the sea. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the southeast, hundreds " +
        "of tall, black oak trees huddle in shadows. The trees eventually " +
        "stretch across the cover the entire eastern horizon as they " +
        "form the Mirkwood forest of legend and lore.\n");


    add_exit(VALE_DIR + "valen4w1", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r03/f07", "southeast");
    add_exit(VALE_DIR + "valen5w0", "east",0,2,1);
    add_exit(VALE_DIR + "valen6w0", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen6w1", "north",0,2,1);
    add_exit(VALE_DIR + "valen6w2", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen5w2", "west",0,2,1);
    add_exit(VALE_DIR + "valen4w2", "southwest",0,2,1); 
}
