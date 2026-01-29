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
    set_long("You are standing on the eastern side of a deep valley, where " +
        "the wide, rushing waters of the Anduin river flow down from " +
        "mountains in the north before running into the lands of Gondor in " +
        "the south before emptying into the sea. The rugged slopes of the " +
        "vale are covered in a tall, yellow-green grass which sways in the " +
        "gentle breezes, constantly brushing up against you. On the far " +
        "side of the valley, rocky foothill march steadily upwards as " +
        "they grow into the jagged peaks of the Misty Mountains. In the " +
        "distance, across the eastern horizon, the black oaks of Mirkwood " +
        "forest stretch out their twisted, crooked branches as if seeking " +
        "victims. The woods are cloaked in deep shadows, looming dark and " +
        "ominous.\n");

    add_exit(VALE_DIR + "valen13w3", "south",0,2,1);
    add_exit(VALE_DIR + "valen13w2", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen14w2", "east",0,2,1);
    add_exit(VALE_DIR + "valen15w2", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen15w3", "north",0,2,1);
    add_exit(VALE_DIR + "valen15w4", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen14w4", "west",0,2,1);
    add_exit(VALE_DIR + "valen13w4", "southwest",0,2,1); 
}
