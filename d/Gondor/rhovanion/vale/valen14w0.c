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
    set_herbs_8();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellowish grass blankets the fields here, swaying and " +
        "brushing against you with every faint breeeze which twists past. " +
        "You are just east of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Tto the west, you " +
        "can see the valley dive down to hold the wide, blue waters of " +
        "the legendary Anduin river as it rushes south towards Gondor and " +
        "the sea. On the other side of the valley, rugged foothills stretch " +
        "high into the sky, piercing the clouds as the majestic " +
        "Misty Mountains of legend. Sprawled all across the eastern " +
        "horizon, an endless forest of tall, black trees waits in dark " +
        "shadows. This is apparently Mirkwood, the fabled woods whose " +
        "name has inspired many tales of terror and woe.\n");

    add_exit(VALE_DIR + "valen13w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r12/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r13/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r14/f08", "northeast");
    add_exit(VALE_DIR + "valen15w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen15w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen14w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen13w1", "southwest",0,2,1); 
}
