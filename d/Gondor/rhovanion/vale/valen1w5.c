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
    set_items_oldroad();
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
        "cast shadow and gloom with their twisted branches. To the south, " +
        "you see what appears to be an old road, cutting across the vale, " +
        "connecting the forest to a wide ford which crosses the river.\n");

    add_exit("/d/Shire/anduin/east/rd02", "south",0,2,1);
    add_exit("/d/Shire/anduin/east/rd03", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen1w4", "east",0,2,1);
    add_exit(VALE_DIR + "valen2w4", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen2w5", "north",0,2,1);
    add_exit(VALE_DIR + "valen2w6", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen1w6", "west",0,2,1);
    add_exit("/d/Shire/anduin/east/rd01", "southwest",0,2,1);   
}
