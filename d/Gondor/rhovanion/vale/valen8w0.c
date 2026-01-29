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
    set_long("You are standing on the eastern edge of a deep valley, whose " +
        "sloping fields are filled with a tall, yellow-green grass which " +
        "bends and sways in the breeze. The valley follows the Anduin, " +
        "whose wide waters rush past on their journey from the mountains " +
        "of the north to the land of Gondor in the south before empting " +
        "out into the sea beyond. Across the wide waters of the river, " +
        "rocky foothills tumble upwards as the Misty Mountains thrust " +
        "their jagged peaks to pierce the sky above. The entire eastern " +
        "horizon is filled with the dark, black trees of Mirkwood, their " +
        "gloomy shadows looming ominously before you in an almost " +
        "menacing manner.\n");

    add_exit(VALE_DIR + "valen7w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r06/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r07/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r08/f08", "northeast");
    add_exit(VALE_DIR + "valen9w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen9w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen8w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen7w1", "southwest",0,2,1); 
}
