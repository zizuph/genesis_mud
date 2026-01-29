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
    set_herbs_8();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellowish grass surrounds you, swaying and bending " +
        "in the wind with every faint breeeze which flutters past. You are " +
        "standing on the eastern edge of the vale of the Anduin, a deep " +
        "valley named for the great river whose rushing waters cut through " +
        "the land as it tumbles down from the north on its journey south to " +
        "the sea. Across the river, on the western bank, rocky foothills " +
        "grow until they pierce the sky with the jagged peaks of the " +
        "legendary Misty Mountains. Immediately to the north and northeast, " +
        "the dark shadows of Mirkwood forest loom behind the crooked " +
        "branches of the tall, black oak trees. The woods spread their " +
        "ominous gloom out to envelop the northern and eastern horizons.\n");

    add_exit(VALE_DIR + "valen15w4", "south",0,2,1);
    add_exit(VALE_DIR + "valen15w3", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen16w3", "east",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r16/f04", "northeast");
    add_forest_entrance(MIRK_C_DIR + "r16/f03", "north");
    add_exit(VALE_DIR + "valen17w5", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen16w5", "west",0,2,1);    
    add_exit(VALE_DIR + "valen15w5", "southwest",0,2,1);  
}


