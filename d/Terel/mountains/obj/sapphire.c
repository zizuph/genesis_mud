/*  A small gem */

inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("sapphire");
    set_adj("glowing");
    set_long("A beautiful shining blue sapphire, it seems to glow.\n");
    add_prop(OBJ_I_VALUE, 8000);
}

