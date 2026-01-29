inherit "/std/object";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_object()
{
    set_name("net");
    set_adj("black");
    add_adj("leather");
    set_short("black leather net");
    set_long("This is a large leather net made of black leather. It "+
    "looks quite strong, and if used properly, it could slow down "+
    "a man-sized object quite easily.\n");
    add_prop(OBJ_I_WEIGHT,150);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,60);
}

