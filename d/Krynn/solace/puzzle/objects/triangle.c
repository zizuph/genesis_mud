/* A wooden triangle. ~solace/puzzle/objects/triangle */

inherit "/std/object";

#include "/sys/stdproperties.h"

void create_object()
{
    set_name("triangle");
    set_adj("painted");
    add_adj("wooden");
    set_long("A triangular wooden block painted a bright red colour.\n");

    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
}
