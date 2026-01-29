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
    set_herbs_7();
    
    set_short("Vale of the Anduin");
    set_long("A warm breeze ripples through the yellow-green grass fields " +
        "which surround you. The fields dip down towards the great river " +
        "Anduin, whose rushing waters churn at the bottom of a deep " +
        "valley. The Anduin flows out of the northern mountains before " +
        "cutting through these fields on its way south towards Gondor " +
        "and the sea. Across the river to the west side of the valley, " +
        "rocky foothills grow into the jagged peaks of the Misty Mountains. " +
        "While to the north and east, an endless forest " +
        "of tall, black oak trees looms menacingly immediately before you. " +
        "This is clearly the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger.\n");

    add_exit(VALE_DIR + "valen14w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r13/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r14/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r15/f08", "northeast");
    add_forest_entrance(MIRK_C_DIR + "r15/f07", "north");
    add_forest_entrance(MIRK_C_DIR + "r15/f06", "northwest");
    add_exit(VALE_DIR + "valen15w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen14w1", "southwest",0,2,1); 
}
