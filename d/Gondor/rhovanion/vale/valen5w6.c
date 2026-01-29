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
    set_herbs_6();
    
    set_short("Vale of the Anduin");
    set_long("You are standing on the eastern side of a deep valley, where " +
        "the wide, rushing waters of the Anduin river flow down from " +
        "mountains in the north before running into the lands of Gondor in " +
        "the south before emptying into the sea. The rugged slopes of the " +
        "vale are covered in a tall, green grass which sways in the " +
        "gentle breezes, constantly brushing up against you. On the far " +
        "side of the valley, rocky foothill march steadily upwards as " +
        "they grow into the jagged peaks of the Misty Mountains. In the " +
        "distance, across the eastern horizon, the black oaks of Mirkwood " +
        "forest stretch out their twisted, crooked branches as if seeking " +
        "victims. The woods are cloaked in deep shadows, looming dark and " +
        "ominous.\n");

    add_exit(VALE_DIR + "valen4w6", "south",0,2,1);
    add_exit(VALE_DIR + "valen4w5", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen5w5", "east",0,2,1);
    add_exit(VALE_DIR + "valen6w5", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen6w6", "north",0,2,1);
    add_exit(VALE_DIR + "valen6w7", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen5w7", "west",0,2,1);
    add_exit(VALE_DIR + "valen4w7", "southwest",0,2,1); 
}
