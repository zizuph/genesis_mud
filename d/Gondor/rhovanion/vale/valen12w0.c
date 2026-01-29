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
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("You are on the eastern edge of a deep valley which stretches " +
        "out of sight to both the north and south. The valley dips down " +
        "in the middle to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. " +
        "Scattered across the rugged slopes are fields filled with a tall, " +
        "yellow-green grass which sways and bends in the wind. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. The eastern horizon is dominated by " +
        "the menacing gloom of Mirkwood forest. Tall, black oak trees are " +
        "barely visible in the dark shadows, their gnarled and crooked " +
        "branches reaching out as if looking for any unsuspecting " +
        "travellers.\n");

    add_exit(VALE_DIR + "valen11w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r10/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r11/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r12/f08", "northeast");
    add_exit(VALE_DIR + "valen13w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen13w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen12w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen11w1", "southwest",0,2,1); 
}
