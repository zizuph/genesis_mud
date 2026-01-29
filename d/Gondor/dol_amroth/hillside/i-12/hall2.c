/*
 * hall2.c
 * 
 * Skippern 20(c)02
 *
 * The living room.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */

/* Code */
void
create_inside()
{
    set_short("a living room");

    set_long("This is a lavish furnished living room.\n");

    add_exit(DOL_HILLS + "i-12/hall1", "north", 0, 1);

}
