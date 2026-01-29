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
    set_herbs_5();
    
    set_short("Vale of the Anduin");
    set_long("You are surrounded by a tall, yellow grass which brushes " +
        "against you as it bends slightly in the breeze. The grass covers " +
        "the rugged slopes of the deep valley you are standing in, following " +
        "the mighty Anduin river as it rushes down from the mountains of " +
        "the north and rolls along south to the sea. Across the river, on " +
        "the west side of the valley, rocky foothills stretch ever upwards, " +
        "growing into the treacherous heights of the legendary Misty " +
        "Mountains. Huddled along the eastern edge of the vale are " +
        "shadowy masses of tall, black trees which loom ominously. This " +
        "is the mighty Mirkwood forest, the source of many tales of " +
        "darkness and doom.\n");

    add_exit(VALE_DIR + "valen8w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen8w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen9w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen10w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen10w7", "north",0,2,1);
}
