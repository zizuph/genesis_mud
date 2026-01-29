inherit "/std/object";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_object()
{
    set_name("water");
    set_short("water");
    set_long("It is the liquid H2O.\n");
    add_name("_kalad_water");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_M_NO_GET,1);
}

