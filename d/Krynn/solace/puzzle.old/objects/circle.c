/* A wooden circle. ~solace/puzzle/objects/circle */

inherit "/std/object";

#include "/sys/stdproperties.h"

void create_object()
{
    set_name("circle");
    set_adj("painted");
    add_adj("wooden");
    set_long("A circular wooden block painted a bright yellow colour.\n");

    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
}
