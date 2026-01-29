/*
 * Path for MM guru quest - /d/Gondor/rhovanion/dolguldur/mirk9.c
 *
 * Varian - January 2021
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "dolguldur/std/base";

/*
 * Function name:        create_dg_room()
 * Description  :        Creates the dg from from the base file
 *                       /d/Gondor/rhovanion/dolguldur/std/base.c
 */
void 
create_dg_room()
{

    set_short("Mirkwood Forest");
    set_long("Looking for the elf in Mirkwood\n");

    add_item( ({"forest", "mirkwood", "mirkwood forest"}),
        "The forest here is full of tall, black trees that devour the " +
        "sunlight, leaving you stranded in a pool of dim shadows.\n");

    add_exit(DG_DIR + "path6", "north", "@@glade@@", 3, 1);
    add_exit(DG_DIR + "path6", "northeast", "@@glade@@", 3, 1);
    add_exit(DG_DIR + "path6", "east", "@@glade@@", 3, 1);
    add_exit(DG_DIR + "path6", "southeast", "@@glade@@", 3, 1);
    add_exit(DG_DIR + "path6", "south", "@@glade@@", 3, 1);
    add_exit(DG_DIR + "path6", "southwest", "@@glade@@", 3, 1);
    add_exit(DG_DIR + "path6", "west", "@@glade@@", 3, 1);
    add_exit(DG_DIR + "path6", "northwest", "@@glade@@", 3, 1);

}

/* A message decribing the journey back to Dol Guldur */
int
glade()
{
    write("You cut back through Mirkwood, making your way back to " +
        "the clearing near Dol Guldur.\n");
    return 0;
}