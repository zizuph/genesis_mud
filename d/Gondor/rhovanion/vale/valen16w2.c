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
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("You are on the eastern edge of the vale of the Anduin, a " +
        "deep valley which holds the great river as the rushing waters " +
        "tumble southwards on their journey to the sea. The rugged " +
        "slopes of the valley are filled with yellow-green grasses " +
        "which bend and sway in the wind as they surround you. On the " +
        "far side of the valley, steep foothills throw their jagged, rocky " +
        "peaks up into the sky where they pierce the heavens as the mighty " +
        "Misty Mountains. Immediately to the east and across the northern " +
        "horizon, the legendary Mirkwood forest looms menacingly. Endless " +
        "rows of tall, black trees stretch out their twisted and crooked " +
        "branches as if seeking to capture an unwary traveller and draw " +
        "them into the dark shadows hidden within.\n");

    add_exit(VALE_DIR + "valen15w2", "south",0,2,1);
    add_exit(VALE_DIR + "valen15w1", "southeast",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r15/f06", "east");
    add_forest_entrance(MIRK_C_DIR + "r16/f06", "northeast");
    add_forest_entrance(MIRK_C_DIR + "r16/f05", "north");
    add_forest_entrance(MIRK_C_DIR + "r16/f04", "northwest");
    add_exit(VALE_DIR + "valen16w3", "west",0,2,1);    
    add_exit(VALE_DIR + "valen15w3", "southwest",0,2,1);  
}


