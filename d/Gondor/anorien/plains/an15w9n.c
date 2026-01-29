/*
 * Anorien - /d/Gondor/anorien/plains/an15w9n.c
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
    set_herbs_1();
    
    set_short("Anorien");
    set_long("You are travelling through the rolling plains of Anorien, " +
        "not far from a dusty stone road which wanders through the land " +
        "to the southwest. The bright " + VBFC("light_type") + " from the " +
        VBFC("sun_moon") + " shines down upon the groves of trees that " +
        "are scattered across the fields of wildflowers and tall green " +
        "grass. To the east, the ruins of Osgiliath sit upon the banks " +
        "of the nearby Anduin River, while to the west, Minas Tirith " +
        "sits upon the edge of the White Mountains before their rocky " +
        "peaks trail off across the horizon.\n");

    add_trees(1);

    add_exit(PLAINS_DIR + "an14w10n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w10n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w9n","west",0,2,1);
    add_exit(PLAINS_DIR + "an14w8n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w8n","north",0,2,1);
    add_exit(PLAINS_DIR + "an16w8n","northeast",0,2,1);
    add_exit(PLAINS_DIR + "an16w9n","east",0,2,1);
    add_exit(PLAINS_DIR + "an16w10n","southeast",0,2,1);
}
