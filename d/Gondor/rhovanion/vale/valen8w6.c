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
    set_long("Gentle breezes drift past, causing the tall, green grass to " +
        "sway and brush against you with every gust. The grassy fields " +
        "follow the rolling slopes of a deep valley, all the way to the " +
        "banks of the Anduin river. Swirling and churning, the powerful " +
        "waters of the great river cut through the land as they tumble " +
        "down from mountains in the north and wander on their journey south " +
        "towards the sea. On the west side of the river, broken foothills " +
        "raise up their rugged faces and thrust jagged peaks up into the " +
        "clouds high above as the majestic Misty Mountains. While to the " +
        "east, endless shadows dance amongst the countless black oaks of " +
        "the legendary Mirkwood forest.\n");

    add_exit(VALE_DIR + "valen7w6", "south",0,2,1);
    add_exit(VALE_DIR + "valen7w5", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen8w5", "east",0,2,1);
    add_exit(VALE_DIR + "valen9w5", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen9w6", "north",0,2,1);
    add_exit(VALE_DIR + "valen9w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen8w7", "west",0,2,1);
    add_exit(VALE_DIR + "valen7w7", "southwest",0,2,1); 
}
