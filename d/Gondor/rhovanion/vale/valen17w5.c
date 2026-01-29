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
    set_long("You are surrounded by fields of a tall, green grass which " +
        "bends and sways in the gentle breeze which drifts past. A deep " +
        "valley stretches out of sight from the north to the south, " +
        "cradling the wide expanse of the Anduin river which tumbles " +
        "southwards on its journey to the sea. To the west, on the far " +
        "bank of the river, rugged foothills leap upwards in a rocky " +
        "ascent until their jagged peaks claw through the wispy clouds " +
        "high above and become known as the Misty Mountains. Mirkwood " +
        "forest covers the horizon to the north and east, where the " +
        "darkest shadows hide behind the twisted branches of black " +
        "oak trees, lying in wait to capture unwary travellers.\n");

    add_exit(VALE_DIR + "valen16w5", "south",0,2,1);
    add_exit(VALE_DIR + "valen16w4", "southeast",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r16/f03", "east");
    add_forest_entrance(MIRK_C_DIR + "r17/f03", "northeast");
    add_forest_entrance(MIRK_C_DIR + "r17/f02", "north");
    add_exit(VALE_DIR + "valen18w6", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen17w6", "west",0,2,1);    
    add_exit(VALE_DIR + "valen16w6", "southwest",0,2,1);  
}


