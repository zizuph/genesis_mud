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
    set_long("You are standing on the eastern edge of a deep valley, where " +
        "the wide, rushing waters of the Anduin river flow down from " +
        "mountains in the north before running into the lands of Gondor in " +
        "the south before emptying into the sea. The rugged slopes of the " +
        "vale are covered in a tall, yellow-green grass which sways in the " +
        "gentle breezes, constantly brushing up against you. On the far " +
        "side of the valley, rocky foothill march steadily upwards as " +
        "they grow into the jagged peaks of the Misty Mountains. Immediately " +
        "across the northern horizon, the tall, black oaks of Mirkwood " +
        "forest stretch out their twisted, crooked branches as if seeking " +
        "victims. The woods spread out to eventually cover the eastern " +
        "horizon, the deep shadows making it difficult for your eyes to " +
        "penetrate the gloom.\n");

    add_exit(VALE_DIR + "valen15w3", "south",0,2,1);
    add_exit(VALE_DIR + "valen15w2", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen16w2", "east",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r16/f05", "northeast");
    add_forest_entrance(MIRK_C_DIR + "r16/f04", "north");
    add_forest_entrance(MIRK_C_DIR + "r16/f03", "northwest");
    add_exit(VALE_DIR + "valen16w4", "west",0,2,1);    
    add_exit(VALE_DIR + "valen15w4", "southwest",0,2,1);  
}


