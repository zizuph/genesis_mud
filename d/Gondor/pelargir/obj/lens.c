/*
 * /d/Gondor/pelargir/obj/lens.c
 *
 * Copyright (C) August 20, 1998 by Ron Miller (Tyr)
 *
 * This is the lens from the Pelargir lighthouse.
 */

#pragma strict_types

inherit     "/std/object";

#include    <stdproperties.h>
#include "/d/Gondor/pelargir/beacon_defs.h"

/*
 * Function name:    create_object
 * Description:      create the basic lens object
 */
void
create_object()
{
    set_name("lens");
    add_name(LENS_NAME);

    set_short("large glass lens");

    set_long("A masterpiece of the glassblower's art, this large "+
        "lens is encircled by a wide metallic band designed to "+
        "incorporate it into some larger mechanism. It seems to "+
        "collect and magnify every available ray of light.\n");

    add_prop(OBJ_I_WEIGHT, 10000);  /* set weight at 10 kg */
    add_prop(OBJ_I_VOLUME, 4000);  /* set volume at 4 Ltr */
} /* end create_object */
