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
    set_herbs_2();
    
    set_short("Vale of the Anduin");
    set_long("Your eyes are filled with the sight of fields of a tall, " +
        "yellow grass that constantly bends and sways in the wind. You are " +
        "on the eastern edge of a deep valley, carved out of the fields " +
        "by the great river Anduin. Powerful and wide, the Anduin flows from " +
        "northern mountains while seeking the sea far to the south. On the " +
        "other side of the valley, rocky foothills reach high into the sky, " +
        "piercing the clouds and earning their name as the Misty Mountains. " +
        "Looming overhead, immediately to the east, are the gloomy depths " +
        "of Mirkwood forest. Black oak trees stand tall and menacing, as " +
        "if waiting for an unwary traveller to mistakenly enter their " +
        "clutches.\n");

    add_exit(VALE_DIR + "valen1w1", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r00/f07", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r01/f07", "east");
    add_forest_entrance(MIRK_C_DIR + "r02/f07", "northeast");
    add_exit(VALE_DIR + "valen3w1", "north",0,2,1);
    add_exit(VALE_DIR + "valen3w2", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen2w2", "west",0,2,1);
    add_exit(VALE_DIR + "valen1w2", "southwest",0,2,1); 
}
