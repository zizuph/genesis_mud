/*
 * Path for MM guru quest - /d/Gondor/rhovanion/dolguldur/mirk6.c
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

    add_exit(DG_DIR + "mirk3", "southwest", "@@glade@@", 3, 1);

}

/* A message decribing a wrong turn */
int
glade()
{
    write("You have clearly made a mistake in following your trail, " +
        "as you have ended up back in a familiar clearing.\n");
    return 0;
}

/* A message decribing the correct path */
int
path()
{
    write("You manage to follow the trail deeper into Mirkwood.\n");
    return 0;
}