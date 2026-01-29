inherit "/std/object";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_object()
{
    set_name("dust");
    add_adj("black");
    set_short("pile of black dust");
    set_pshort("piles of black dust");
    set_long("It is a large pile of black dust.\n");
    add_name("_kalad_dust");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
}

