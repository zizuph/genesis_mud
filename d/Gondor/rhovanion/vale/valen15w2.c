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
    set_herbs_3();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellow-green grass encompasses you as it sways in the " +
        "wind, brushing against your legs with every breeze which swirls " +
        "past. You are standing just east of a deep valley which cuts " +
        "through the land from north to south. This is the vale of the " +
        "Anduin, named for the great river which tumbles south towards " +
        "the sea. Across the river, on the west side of the valley, " +
        "you can see rugged foothills huddled at the feet of the Misty " +
        "Mountains which reach high into the clouds which give them " +
        "their name. Hundreds of tall, black oak trees cloak themselves " +
        "in shadow and gloom immediately to the northeast, the edge of " +
        "Mirkwood. The great forest stretches out across the distant horizon " +
        "to both the north and the east.\n");

    add_exit(VALE_DIR + "valen14w2", "south",0,2,1);
    add_exit(VALE_DIR + "valen14w1", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen15w1", "east",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r15/f06", "northeast");
    add_exit(VALE_DIR + "valen16w2", "north",0,2,1);
    add_exit(VALE_DIR + "valen16w3", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen15w3", "west",0,2,1);
    add_exit(VALE_DIR + "valen14w3", "southwest",0,2,1); 
}
