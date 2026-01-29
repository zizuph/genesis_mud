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
    set_herbs_8();
    
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

    add_exit(VALE_DIR + "valen13w4", "south",0,2,1);
    add_exit(VALE_DIR + "valen13w3", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen14w3", "east",0,2,1);
    add_exit(VALE_DIR + "valen15w3", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen15w4", "north",0,2,1);
    add_exit(VALE_DIR + "valen15w5", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen14w5", "west",0,2,1);
    add_exit(VALE_DIR + "valen13w5", "southwest",0,2,1); 
}
