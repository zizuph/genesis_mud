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
    set_herbs_9();
    
    set_short("Vale of the Anduin");
    set_long("A tall, green grass surrounds you, swaying in the breeze and " +
        "brushing up against your legs. You are standing just on the " +
        "eastern edge of the vale of the Anduin, the deep valley which " +
        "follows the great river as it flows down from the mountains in the " +
        "north before rushing south to empty out into the sea. On the " +
        "west side of the valley, rocky foothills march brokenly away " +
        "from the river, climbing ever higher until their jagged peaks " +
        "pierce the sky as the legendary Misty Mountains. To the east, " +
        "the oppressive darkness and shadows of Mirkwood forest loom " +
        "in a menacing manner. Endless oaks, tall and black, seem to " +
        "stretch their crooked branches out to clutch at any traveller " +
        "foolish enough to come within their reach.\n");

    add_exit(VALE_DIR + "valen11w2", "south",0,2,1);
    add_exit(VALE_DIR + "valen11w1", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen12w1", "east",0,2,1);
    add_exit(VALE_DIR + "valen13w1", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen13w2", "north",0,2,1);
    add_exit(VALE_DIR + "valen13w3", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen12w3", "west",0,2,1);
    add_exit(VALE_DIR + "valen11w3", "southwest",0,2,1); 
}
