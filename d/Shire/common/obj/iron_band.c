/*
 * Band of iron used to fix wagon wheel in quest.
 * -- Finwe January 2005
 */

#pragma save_binary
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";


create_object()
{
    set_name(({"_shire_iron_band", "iron band", "iron strip", "band", "strip"}));
    set_adj(({"long", "narrow"}));
    set_short("long iron strip");
    set_long("This is a long strip of iron. It is used to repair wheels. " +
        "There are two holes at each end of it where nails can be hammered " +
        "through it to iron strip in place.\n");

   add_prop(OBJ_I_WEIGHT, 4000);
   add_prop(OBJ_I_VALUE, 230);
   add_prop(OBJ_I_VOLUME, 1000);
}

