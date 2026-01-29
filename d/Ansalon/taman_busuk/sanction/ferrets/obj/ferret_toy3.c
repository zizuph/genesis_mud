
/*
 * ferret_toy3.c
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
    set_name("ball");
    set_adj(({ "blue", "checkered" }));
    set_long("This is a blue checkered ball. Ferrets love "+
    "rolling it around on the floor. \n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,2);
    add_prop(OBJ_I_VALUE, 1);
}
