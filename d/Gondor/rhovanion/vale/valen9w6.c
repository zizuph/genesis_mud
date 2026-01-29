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
    set_long("A tall, yellow grass surrounds you, swaying and brushing " +
        "against your legs with every faint breeeze which twists past. " +
        "Standing on the eastern slopes of a deep valley which stretches out " +
        "of sight to both the north and the south, you can see how the " +
        "vale dips down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "west side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the rugged " +
        "Misty Mountains. To the east, an endless forest " +
        "of tall, black oak trees looms menacingly, casting dark shadows as " +
        "the mighty Mirkwood forest of legend and lore.\n");

    add_exit(VALE_DIR + "valen8w6", "south",0,2,1);
    add_exit(VALE_DIR + "valen8w5", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen9w5", "east",0,2,1);
    add_exit(VALE_DIR + "valen10w5", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen10w6", "north",0,2,1);
    add_exit(VALE_DIR + "valen10w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen9w7", "west",0,2,1);
    add_exit(VALE_DIR + "valen8w7", "southwest",0,2,1); 
}
