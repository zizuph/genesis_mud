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
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("A warm breeze ripples through the yellow-green grass fields " +
        "which surround you. The fields dip down towards the great river " +
        "Anduin, whose rushing waters churn at the bottom of a deep " +
        "valley. The Anduin flows out of the northern mountains before " +
        "cutting through these fields on its way south towards Gondor " +
        "and the sea. Across the river to the west side of the valley, " +
        "rocky foothills grow into the jagged peaks of the Misty Mountains. " +
        "While across the eastern horizon, an endless forest " +
        "of tall, black oak trees blankets the land in dark shadows. These " +
        "woods are better known as Mirkwood, the legendary forest of " +
        "many dark and deadly tales.\n");

    add_exit(VALE_DIR + "valen3w2", "south",0,2,1);
    add_exit(VALE_DIR + "valen3w1", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen4w1", "east",0,2,1);
    add_exit(VALE_DIR + "valen5w1", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen5w2", "north",0,2,1);
    add_exit(VALE_DIR + "valen5w3", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen4w3", "west",0,2,1);
    add_exit(VALE_DIR + "valen3w3", "southwest",0,2,1); 
}
