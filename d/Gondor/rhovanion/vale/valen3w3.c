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
    set_herbs_4();
    
    set_short("Vale of the Anduin");
    set_long("You are near the banks of the massive river Anduin, whose " +
        "powerful waters have carved out a deep valley as they travel south " +
        "towards Gondor where they empty out into the sea. The slopes of " +
        "the vale are rugged and filled with a tall, yellow-green grass " +
        "which sways and brushes against you in the breeze. On the far " +
        "side of the river, rocky foothills eventually stretch their " +
        "jagged peaks into the sky, reaching for the heavens as the mighty " +
        "Misty Mountains of legend. Across the eastern horizon, the " +
        "infamous Mirkwood forest sprawls haphazardly, as tall, black oaks " +
        "cast shadow and gloom with their twisted branches.\n");

    add_exit(VALE_DIR + "valen2w3", "south",0,2,1);
    add_exit(VALE_DIR + "valen2w2", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen3w2", "east",0,2,1);
    add_exit(VALE_DIR + "valen4w2", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen4w3", "north",0,2,1);
    add_exit(VALE_DIR + "valen4w4", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen3w4", "west",0,2,1);
    add_exit(VALE_DIR + "valen2w4", "southwest",0,2,1); 
}
