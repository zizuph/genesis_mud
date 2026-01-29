#pragma strict_types
#include "defs.h"
inherit "/std/object";

void
create_object()
{
    set_name("foundation");
    set_adj(({"new","wood"}));
    set_short("new wood foundation");
    set_long("It is the beginnings of wooden buildling, set on pilings in " +
      "the sand. It looks like it is about half-way through construction.\n");
    add_prop(OBJ_M_NO_GET, "The " + QSHORT(TO) + " is firmly embedded"
    +" in the ground.\n");
    add_prop(OBJ_I_WEIGHT, 400000);
    add_prop(OBJ_I_VOLUME, 16000);
}
