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
    set_long("You are completely surrounded by a tall, yellowish grass which " +
        "blankets the sloping hills in all directions. Standing near the " +
        "eastern bank of the Anduin, deep in the vallery, you watch as the " +
        "rushing waters tumble past, running fast on their journey south " +
        "towards the sea. The rocky foothills on the west side of the valley " +
        "quickly march upwards, growing into the legendary Misty Mountains " +
        "whose peaks pierce the cloudy skies above. Mirkwood forest hovers " +
        "over the eastern edge of the valley, with tall, black trees which " +
        "loom ominously as if watching your every move, waiting for you to " +
        "carelessly enter their embrace.\n");

    add_exit(VALE_DIR + "valen5w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen5w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen6w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen7w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen7w7", "north",0,2,1);
}
