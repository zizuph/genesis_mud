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
    set_herbs_7();
    
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
        "filled with the gloom of the deepest and darkest shadows.\n");

    add_exit(VALE_DIR + "valen4w4", "south",0,2,1);
    add_exit(VALE_DIR + "valen4w3", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen5w3", "east",0,2,1);
    add_exit(VALE_DIR + "valen6w3", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen6w4", "north",0,2,1);
    add_exit(VALE_DIR + "valen6w5", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen5w5", "west",0,2,1);
    add_exit(VALE_DIR + "valen4w5", "southwest",0,2,1); 
}
