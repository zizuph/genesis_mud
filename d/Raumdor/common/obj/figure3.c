/* The Necronomicon */
#include "defs.h"
inherit "/std/object";

void
create_object()
{
    set_name("figure");
    set_adj("strange");
    set_short("strange figure");
    set_long("The figure looks like a bunch of sticks stuck together:\n"+
    "\n"+
    "     x\n"+
    "    /\n"+
    "   x\n"+
    "  /\n"+
    " 9\n");


    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,40);
}
