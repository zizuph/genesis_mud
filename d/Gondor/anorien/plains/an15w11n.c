/*
 * Anorien - /d/Gondor/anorien/plains/an15w11n.c
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
    set_items_road();
    set_items_city();
    set_herbs_8();
    
    set_short("Anorien");
    set_long("You are wandering along the southern edge of the rolling " +
        "plains that stretch across Anorien. The fields of wildflowers " +
        "and tall green grass are interupted by the Anruin River running " +
        "through the ruins of Osgiliath to the east and Rammas Echor " +
        "standing tall on the other side of the dusty road that passes to " +
        "the south. To the west, Minas Tirith stands tall, watching the " +
        "lands from its perch on the eastern edge of the White " +
        "Mountains that stretch up into the " + VBFC("day_time") + 
        " sky above.\n");

    add_trees(1);

    add_exit(ROAD_DIR + "or1","southwest",0,2,1);
    add_exit(ROAD_DIR + "or2","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w11n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w10n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w10n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w10n","northeast",0,2,1);
    add_exit(PLAINS_DIR + "an16w11n","east",0,2,1);
}
