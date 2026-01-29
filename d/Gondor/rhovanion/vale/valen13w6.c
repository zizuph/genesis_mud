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
    set_herbs_5();
    
    set_short("Vale of the Anduin");
    set_long("You are standing on the eastern side of a deep valley, where " +
        "the wide, rushing waters of the Anduin river flow down from " +
        "mountains in the north before running into the lands of Gondor in " +
        "the south before emptying into the sea. The rugged slopes of the " +
        "vale are covered in a tall, yellowish grass which sways in the " +
        "gentle breezes, constantly brushing up against you. On the far " +
        "side of the valley, rocky foothill march steadily upwards as " +
        "they grow into the jagged peaks of the Misty Mountains. In the " +
        "distance, across the eastern horizon, the black oaks of Mirkwood " +
        "forest stretch out their twisted, crooked branches as if seeking " +
        "victims. The woods are cloaked in deep shadows, looming dark and " +
        "ominous.\n");

    add_exit(VALE_DIR + "valen12w6", "south",0,0,1);
    add_exit(VALE_DIR + "valen12w5", "southeast",0,0,1);
    add_exit(VALE_DIR + "valen13w5", "east",0,0,1);
    add_exit(VALE_DIR + "valen14w5", "northeast",0,0,1);
    add_exit(VALE_DIR + "valen14w6", "north",0,0,1);
    add_exit(VALE_DIR + "valen14w7", "northwest",0,0,1);
    add_exit(VALE_DIR + "valen13w7", "west",0,0,1);
    add_exit(VALE_DIR + "valen12w7", "southwest",0,0,1); 
}
