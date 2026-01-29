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
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellow-green grass surrounds you, bending as it sways " +
        "in the gentle gusts and breezes which drift past. You are standing " +
        "on the eastern slopes of a deep valley which cuts through the " +
        "fields from the north to the south. West of here, the valley dips " +
        "down to cradle the wide, rushing waters of the legendary Anduin " +
        "river as it flows towards Gondor before emptying into the sea. On " +
        "the far side of the valley, you can see the rugged face of " +
        "broken foothills as they stretch up to pierce the sky as the " +
        "mighty Misty Mountains. Sprawling across the entire eastern " +
        "horizon, endless lines of tall, black oak trees reach out with " +
        "their twisted, crooked branches as they mark the boundary of " +
        "Mirkwood. It is clear, even from a distance, that the forest is " +
        "filled with the gloom of the deepest and darkest shadows. " +
        "Not far to the south, " +
        "you see what appears to be an old road, cutting across the vale, " +
        "connecting the forest to a wide ford which crosses the river.\n");

    add_exit("/d/Shire/anduin/east/rd05", "south",0,2,1);
    add_exit(MIRK_OR_DIR + "r01", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen1w1", "east",0,2,1);
    add_exit(VALE_DIR + "valen2w1", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen2w2", "north",0,2,1);
    add_exit(VALE_DIR + "valen2w3", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen1w3", "west",0,2,1);
    add_exit("/d/Shire/anduin/east/rd04", "southwest",0,2,1);   
}
