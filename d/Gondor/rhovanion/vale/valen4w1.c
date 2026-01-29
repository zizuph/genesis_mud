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
    set_herbs_4();
    
    set_short("Vale of the Anduin");
    set_long("Standing upon the estern edge of a deep valley, you can see " +
        "the great river Anduin below, as the wide, powerful waters carve " +
        "through endless fields of tall, yellow grass. Flowing down from " +
        "the north, this massive river runs tirelessly on the long " +
        "journey south towards the sea. On the west side of the vale, broken " +
        "foothills march upwards into the mighty Misty Mountains, whose " +
        "tall, jagged peaks pierce the very sky. An endless forest of tall, " +
        "black oak trees looms menacingly immediately before you to the " +
        "east, marking the edge of the deadly Mirkwood Forest.\n");

    add_exit(VALE_DIR + "valen3w1", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r02/f07", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r03/f07", "east");
    add_exit(VALE_DIR + "valen5w0", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen5w1", "north",0,2,1);
    add_exit(VALE_DIR + "valen5w2", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen4w2", "west",0,2,1);
    add_exit(VALE_DIR + "valen3w2", "southwest",0,2,1); 
}
