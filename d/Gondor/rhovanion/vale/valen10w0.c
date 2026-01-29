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
    set_long("A tall, yellow-green grass surrounds you, bending and brushing " +
        "against you with every gentle breeeze which twirls past. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. To the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "west side of the valley there are rugged foothills which stretch " +
        "high into the heavens above, their jagged peaks piercing the sky " +
        "earning their name as the Misty Mountains of legend. The entire " +
        "eastern horizon is filled with the oppressive gloom of Mirkwood, " +
        "where the tall, black oak trees appear to reach out their crooked " +
        "branches to snatch away a careless traveller.\n");

    add_exit(VALE_DIR + "valen9w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r08/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r09/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r10/f08", "northeast");
    add_exit(VALE_DIR + "valen11w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen11w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen10w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen9w1", "southwest",0,2,1); 
}
