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
    set_long("A tall, yellow-green grass surrounds you, swaying and brushing " +
        "against your legs with every faint breeeze which twists past. You " +
        "are on the eastern edge of a deep valley which stretches beyond " +
        "sight to both the north and the south. Directly to the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they pierce the clouds as the majestic " +
        "Misty Mountains. To the northeast you can see Mirkwood forest, " +
        "where endless shadows hide behind the crooked branches of " +
        "sinister looking oak trees.\n");

    add_exit(VALE_DIR + "valen16w6", "south",0,2,1);
    add_exit(VALE_DIR + "valen16w5", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen17w5", "east",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r17/f02", "northeast");
    add_exit(VALE_DIR + "valen18w6", "north",0,2,1);
    add_exit(VALE_DIR + "valen18w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen17w7", "west",0,2,1);    
    add_exit(VALE_DIR + "valen16w7", "southwest",0,2,1);  
}


