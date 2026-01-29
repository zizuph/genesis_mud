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
    set_items_oldroad();
    set_herbs_3();
    
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
        "the legendary Mirkwood forest. Not far to the south, " +
        "you see what appears to be an old road, cutting across the vale, " +
        "connecting the forest to a wide ford which crosses the river.\n");

    add_exit("/d/Shire/anduin/east/rd03", "south",0,2,1);
    add_exit("/d/Shire/anduin/east/rd04", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen1w3", "east",0,2,1);
    add_exit(VALE_DIR + "valen2w3", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen2w4", "north",0,2,1);
    add_exit(VALE_DIR + "valen2w5", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen1w5", "west",0,2,1);
    add_exit("/d/Shire/anduin/east/rd02", "southwest",0,2,1);   
}
