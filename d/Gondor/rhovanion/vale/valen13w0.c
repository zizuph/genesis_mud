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
    set_herbs_9();
    
    set_short("Vale of the Anduin");
    set_long("A tall, green grass surrounds you, swaying and brushing " +
        "against your legs with every faint breeeze which twists past. " +
        "Standing on the eastern edge of a deep valley which stretches out " +
        "of sight to both the north and the south, you can see how the " +
        "vale dips down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "west side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the rugged " +
        "Misty Mountains. To the east, an endless forest " +
        "of tall, black oak trees looms menacingly immediately before you. " +
        "This is clearly the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger.\n");

    add_exit(VALE_DIR + "valen12w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r11/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r12/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r13/f08", "northeast");
    add_exit(VALE_DIR + "valen14w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen14w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen13w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen12w1", "southwest",0,2,1); 
}
