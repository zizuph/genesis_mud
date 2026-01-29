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
        "whose rugged fields are filled with a tall, yellow grass which " +
        "bends and sways in the breeze. Following the mighty Anduin river, " +
        "the valley stretches beyond what your eye can see, from the " +
        "mountains of the north to Gondor and the sea beyond to the south. " +
        "To the west, across the wide waters of the river, " +
        "rocky foothills climb upwards as the Misty Mountains thrust " +
        "their jagged peaks to pierce the heavens above. The entire eastern " +
        "horizon is filled with the dark, black trees of Mirkwood, their " +
        "gloomy shadows looming ominously before you in an almost " +
        "menacing manner.\n");

    add_exit(VALE_DIR + "valen3w3", "south",0,2,1);
    add_exit(VALE_DIR + "valen3w2", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen4w2", "east",0,2,1);
    add_exit(VALE_DIR + "valen5w2", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen5w3", "north",0,2,1);
    add_exit(VALE_DIR + "valen5w4", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen4w4", "west",0,2,1);
    add_exit(VALE_DIR + "valen3w4", "southwest",0,2,1); 
}
