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
    set_herbs_3();
    
    set_short("Vale of the Anduin");
    set_long("Tall, yellow grass grows in a field all around you, swaying " +
        "with the faint breeeze and brushing up against you. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Nearby, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "west side of the valley, rugged foothills stretch higher and " +
        "higher until they seemingly touch the skies as the legendary " +
        "Misty Mountains. Thousands of tall, black oak trees loom ominously " +
        "above you to the east, as you are on the very edge of the " +
        "shadowy Mirkwood forest.\n");

    add_exit(VALE_DIR + "valen2w1", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r01/f07", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r02/f07", "east");
    add_forest_entrance(MIRK_C_DIR + "r03/f07", "northeast");
    add_exit(VALE_DIR + "valen4w1", "north",0,2,1);
    add_exit(VALE_DIR + "valen4w2", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen3w2", "west",0,2,1);
    add_exit(VALE_DIR + "valen2w2", "southwest",0,2,1); 
}
