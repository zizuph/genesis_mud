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
    set_long("Tall, yellow-green grass fills these fields, swaying and " +
        "brushing against you with every faint, passing breeeze. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. To the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the east, an endless forest " +
        "of tall, black oak trees looms menacingly immediately before you. " +
        "This is clearly the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger.\n");

    add_exit(VALE_DIR + "valen8w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r07/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r08/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r09/f08", "northeast");
    add_exit(VALE_DIR + "valen10w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen10w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen9w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen8w1", "southwest",0,2,1); 
}
