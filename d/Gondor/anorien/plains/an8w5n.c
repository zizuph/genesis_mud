/*
 * Anorien - /d/Gondor/anorien/plains/an8w5n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

/*
 * Function name:        create_plains_room()
 * Description  :        Creates the plains from from the base file
 *                       /d/Gondor/anorien/std/base.c
 */
void 
create_plains_room()
{
    set_items_plains();
    set_items_road();
    set_herbs_2();
    
    set_short("Anorien");
    set_long("You are standing beneath the " + VBFC("sun_moon") + " as it " +
        "shines down upon the rolling plains of Anorien. Tall green grass " +
        "surrounds you, brushing against you as it sways in the wind. " +
        "Colourful clusters of wildflowers are scattered across the fields, " +
        "interupted by the occasional grove of trees. A dusty stone road " +
        "passes nearby to the south, running in front of the jagged " +
        "peaks of the White Mountains the stretch up towards the " +
        VBFC("day_desc") + " sky above. In the distance to the north, " +
        "the gentle waters of the Entwash slowly wind their way to the " +
        "Anduin River which cuts through the land far off to the east.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "wr8","southwest",0,2,1);
    add_exit(ROAD_DIR + "wr7","south",0,2,1);
    add_exit(ROAD_DIR + "wr6","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an7w5n","west",0,2,1);
    add_exit(PLAINS_DIR + "an9w5n","east",0,2,1);
    add_exit(PLAINS_DIR + "an7w4n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an8w4n","north",0,2,1);
    add_exit(PLAINS_DIR + "an9w4n","northeast",0,2,1);
}
