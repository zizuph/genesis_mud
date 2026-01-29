
/*
 * ferret_toy.c
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
    set_adj(({ "small", "fluffy" }));
    set_long("This small fluffy ferret toy has entertained the ferrets for "+
    "quite some time by the looks of it. No doubt several ferrets have "+
    "played tug-a-war with it.\n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,2);
    add_prop(OBJ_I_VALUE, 1);
}
