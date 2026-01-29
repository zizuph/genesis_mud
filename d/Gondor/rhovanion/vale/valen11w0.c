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
    set_herbs_2();
    
    set_short("Vale of the Anduin");
    set_long("The sloping fields surrounding you are filled with the tall, " +
        "green grass that brushes against your legs with every gentle " +
        "breeze which drifts past. You are standing on the eastern edge " +
        "of a deep valley, carved out of the earth by the Anduin. The great " +
        "river is wide, with its rushing waters rumbling southwards on " +
        "the long journey to the sea. On the far side of the valley, " +
        "rough and rugged foothills tumble up and away, reaching high " +
        "into the clouds above where they are aptly named the Misty " +
        "Mountains. To the east, the entire horizon is filled with dark " +
        "shadows cast by massive, black oak trees. Mirkwood forest is " +
        "known in legend and lore as a place of great danger for any " +
        "unwary traveller who might enter the gloom carelessly.\n");

    add_exit(VALE_DIR + "valen10w0", "south",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r09/f08", "southeast");
    add_forest_entrance(MIRK_C_DIR + "r10/f08", "east");
    add_forest_entrance(MIRK_C_DIR + "r11/f08", "northeast");
    add_exit(VALE_DIR + "valen12w0", "north",0,2,1);
    add_exit(VALE_DIR + "valen12w1", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen11w1", "west",0,2,1);
    add_exit(VALE_DIR + "valen10w1", "southwest",0,2,1); 
}
