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
    set_herbs_6();
    
    set_short("Vale of the Anduin");
    set_long("You are now upon the eastern edge of a deep, rocky valley, " +
        "whose sloping fields are filled with a tall, green grass which" +
        "bends and sways in the breeze. Following the mighty Anduin river, " +
        "the valley stretches beyond what your eye can see, from the " +
        "mountains of the north to Gondor and the sea beyond to the south. " +
        "To the west, across the wide waters of the river, " +
        "rugged foothills climb upwards as the Misty Mountains thrust " +
        "their rocky peaks to pierce the heavens above. The entire eastern " +
        "horizon is filled with the dark, black trees of Mirkwood, their " +
        "gloomy shadows looming ominously before you in an almost " +
        "menacing manner.\n");

    add_exit(VALE_DIR + "valen6w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r05/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r06/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r07/f08", "northeast");
    add_exit(VALE_DIR + "valen8w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen8w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen7w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen6w1", "southwest",0,2,1); 
}
