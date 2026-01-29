/*
 * /d/Gondor/pelargor/obj/mirror.c
 *
 * Copyright (C) June 24, 1998 by Ron Miller (Tyr)
 *
 * This is the mirror from the Pelargir lighthouse.
 * 
 * Revision History:
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 *
 */

#pragma strict_types

inherit     "/std/object";

#include    <stdproperties.h>
#include "/d/Gondor/pelargir/beacon_defs.h"

/*
 * Function name:    create_object
 * Description:      create the basic mirror object
 */
void
create_object()
{
    set_name("mirror");
    add_name(MIRROR_NAME);

    set_short("large circular mirror");

    set_long("This large circular mirror is clearly not intended "+
        "for use as a personal grooming aid.  Its broad, concave "+
        "surface does not produce true reflections, but it is "+
        "well-suited for use in an optical instrument to gather and "+
        "focus rays of light. The metal ring around its "+
        "circumference makes it appear to be a piece from some "+
        "much larger mechanism.\n");

    add_prop(OBJ_I_WEIGHT, 15000);  /* set weight at 15 kg */
    add_prop(OBJ_I_VOLUME, 6000);  /* set volume at 6 Ltr */
} /* end create_object */
