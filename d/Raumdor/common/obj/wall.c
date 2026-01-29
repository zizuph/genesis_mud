#pragma strict_types
#include "defs.h"
inherit "/std/object";

void
create_object()
{
    set_name("wall");
    set_adj(({"short","stone"}));
    set_short("short stone wall");
    set_long("It is the beginnings of stone wall, running north to south " +
        "with a wide gap providing a passage east. It's about waist-high. " +
        "It looks like it is in the middle of construction.\n");
    add_prop(OBJ_M_NO_GET, "The " + QSHORT(TO) + " is firmly embedded"
    +" in the ground.\n");
    add_prop(OBJ_I_WEIGHT, 4000000);
    add_prop(OBJ_I_VOLUME, 160000);
}
