/* A wooden star. ~solace/puzzle/objects/star */

inherit "/std/object";

#include "/sys/stdproperties.h"

void create_object()
{
    set_name("star");
    set_adj("painted");
    add_adj("wooden");
    set_long("A star-shaped wooden block painted a dark blue colour.\n");

    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
}
