
/*
 * ferret_toy2.c
 * Just a toy, not used for anything.
 * 
 * Ares, 2004
 *
 */
 
inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


void
create_object()
{
    set_name("toy");
    set_adj(({ "little", "round" }));
    set_long("This is a little round ferret toy. Watch them "+
    "chase it around until they hide it. \n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,2);
    add_prop(OBJ_I_VALUE, 1);
}
