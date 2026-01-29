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
    set_herbs_4();
    
    set_short("Vale of the Anduin");
    set_long("Standing on the eastern bank of the mighty Anduin river, you " +
        "can see the tall, swaying grasses of the vale surround you " +
        "completely. The rugged slopes of the valley appear to stand guard " +
        "over the river as it traves south on the journey towards the sea. " +
        "Across the river to the west, rocky foothills stretch higher and " +
        "higher as they reach into the clouds above, where they at once " +
        "become known as the Misty Mountains. To the east, an endless forest " +
        "of tall, black oak trees loom menacingly. This can only be the " +
        "infamous Mirkwood, the legendary forest which has been the subject " +
        "of many terrifying tales.\n");

    add_exit(VALE_DIR + "valen9w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen9w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen10w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen11w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen11w7", "north",0,2,1);
}
