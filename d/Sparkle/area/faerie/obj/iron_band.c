/*
 * Band of iron used to fix wagon wheel in quest.
 * -- Finwe January 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

create_object()
{
    set_name(({"_faerie_iron_band", "iron band", "iron strip", "band", "strip"}));
    set_adj(({"long", "narrow"}));
    set_short("long iron strip");
    set_long("This is a long strip of iron. It is used to repair wheels. " +
        "There are two holes at each end of it where nails can be hammered " +
        "through it to hold it in place on a wagon wheel.\n");

   add_prop(OBJ_I_WEIGHT, 4000);
   add_prop(OBJ_I_VALUE, 230);
   add_prop(OBJ_I_VOLUME, 1000);
}

