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
    set_long("You are surrounded by fields of a tall, yellow grass which " +
        "bends and sways in the gentle breeze which drifts past. A deep " +
        "valley stretches out of sight from the north to the south, " +
        "cradling the wide expanse of the Anduin river which tumbles " +
        "southwards on its journey to the sea. To the west, on the far " +
        "bank of the river, rugged foothills leap upwards in a rocky " +
        "ascent until their jagged peaks claw through the wispy clouds " +
        "high above and become known as the Misty Mountains. Mirkwood " +
        "forest covers the horizon far to the east, where the " +
        "darkest shadows hide behind the twisted branches of black " +
        "oak trees, lying in wait to capture unwary travellers.\n");

    add_exit(VALE_DIR + "valen13w2", "south",0,2,1);
    add_exit(VALE_DIR + "valen13w1", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen14w1", "east",0,2,1);
    add_exit(VALE_DIR + "valen15w1", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen15w2", "north",0,2,1);
    add_exit(VALE_DIR + "valen15w3", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen14w3", "west",0,2,1);
    add_exit(VALE_DIR + "valen13w3", "southwest",0,2,1); 
}
