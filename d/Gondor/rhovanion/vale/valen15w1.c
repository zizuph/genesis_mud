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
    set_herbs_6();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellowish grass surrounds you, swaying and brushing " +
        "against you with every faint breeeze which twists past you. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Directly to the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until their jagged peaks hide in the clouds as the legendary " +
        "Misty Mountains. Tall, black oak trees loom menacingly immediately " +
        "to the north and northeast, the fringes of Mirkwood. Deep shadows " +
        "and menacing gloom seem to await any traveller who might foolishly " +
        "enter the forest.\n");

    add_exit(VALE_DIR + "valen14w1", "south",0,2,1);
    add_exit(VALE_DIR + "valen14w0", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen15w0", "east",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r15/f07", "northeast");
    add_forest_entrance(MIRK_C_DIR + "r15/f06", "north");
    add_exit(VALE_DIR + "valen16w2", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen15w2", "west",0,2,1);
    add_exit(VALE_DIR + "valen14w2", "southwest",0,2,1); 
}
