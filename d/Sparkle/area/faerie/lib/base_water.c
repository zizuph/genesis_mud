/*
 * This file contains the routines necessary to enable players to drink 
 * from rivers, fountains, etc. 
 * The code is based on Gondor's drinking routines.
 * - Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";

/*
 * Function name:	init
 * Description	:	add the drinking and river verbs
 */
public void
init()
{
    ::init();
    init_drink();
}

/*
 * Function name:	drink_message
 * Description	:	do the msgs for drinking from river
 */
public void
drink_message(string from)
{
    write("You drink some water from the " + from + ". It is crisp and " +
        "cool tasting.\n");
    say(QCTNAME(TP)+" drinks some water from the " + from + ".\n");
} /* drink_message */
