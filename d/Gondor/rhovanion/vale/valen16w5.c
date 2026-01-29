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
    set_herbs_7();
    
    set_short("Vale of the Anduin");
    set_long("The tall, yellowish grass which surrounds you sways in the " +
        "gentle breeze which drifts past, brushing up against your legs. You " +
        "are standing on the eastern edge of a deep valley, stretching " +
        "from the north to the south. Directly to the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "other side of the valley, rocky foothills reach upwards as their " +
        "jagged peaks pierce the sky as the legendary Misty Mountains. To " +
        "the northeast, endless lines of tall, black oak trees stretch " +
        "out to eventually encompass the entire eastern and northern " +
        "horizons as the dark shadows of the mighty Mirkwood forest " +
        "looms nearby.\n");

    add_exit(VALE_DIR + "valen15w5", "south",0,2,1);
    add_exit(VALE_DIR + "valen15w4", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen16w4", "east",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r16/f03", "northeast");
    add_exit(VALE_DIR + "valen17w5", "north",0,2,1);
    add_exit(VALE_DIR + "valen17w6", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen16w6", "west",0,2,1);    
    add_exit(VALE_DIR + "valen15w6", "southwest",0,2,1);  
}


