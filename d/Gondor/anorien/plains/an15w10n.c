/*
 * Anorien - /d/Gondor/anorien/plains/an15w10n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

void 
create_plains_room()
{
    set_items_plains();
    set_items_city();
    set_items_road();
    set_herbs_9();
    
    set_short("Anorien");
    set_long("It is " + VBFC("day_desc") + " in the lands of Anorien, and " +
        "you watch as the " + VBFC("light_type") + " plays on the colourful " +
        "wildflowers that hide beneath the tall green grass and behind " +
        "the hundreds of trees that have gathered in groves. A dusty road " +
        "cuts across the rolling plains to the south, as Rammas Echor " +
        "stands vigilantly on the other side. To the east, the ruins of " +
        "Osgiliath sit astride the churning waters of the Anduin River, " +
        "while the citadel of Minas Tirith overlooks it all from its " +
        "perch high upon the slopes of the White Mountains to the west.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w11n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w11n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w10n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w9n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w9n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w9n","northeast",0,2,1);
    add_exit(PLAINS_DIR + "an16w10n","east",0,2,1);
    add_exit(PLAINS_DIR + "an16w11n","southeast",0,2,1);
}
