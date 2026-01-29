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
    set_herbs_3();
    
    set_short("Vale of the Anduin");
    set_long("You are now upon the eastern slopes of a deep, rocky valley, " +
        "whose rugged fields are filled with a tall, yellowish grass which " +
        "bends and sways in the breeze. Following the mighty Anduin river, " +
        "the valley stretches beyond what your eye can see, from the " +
        "mountains of the north to Gondor and the sea beyond to the south. " +
        "To the west, across the wide waters of the river, " +
        "rocky foothills climb upwards as the Misty Mountains thrust " +
        "their jagged peaks to pierce the heavens above. The entire eastern " +
        "horizon is filled with the dark, black trees of Mirkwood, their " +
        "gloomy shadows looming ominously before you in an almost " +
        "menacing manner.\n");

    add_exit(VALE_DIR + "valen10w6", "south",0,2,1);
    add_exit(VALE_DIR + "valen10w5", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen11w5", "east",0,2,1);
    add_exit(VALE_DIR + "valen12w5", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen12w6", "north",0,2,1);
    add_exit(VALE_DIR + "valen12w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen11w7", "west",0,2,1);
    add_exit(VALE_DIR + "valen10w7", "southwest",0,2,1); 
}
