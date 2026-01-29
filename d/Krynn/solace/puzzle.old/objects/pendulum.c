/* Pendulum for grandfather clock. ~solace/puzzle/objects/pendulum */

inherit "/std/object";

#include "/sys/stdproperties.h"
   
void create_object()
{
    set_name("pendulum");
    set_adj("heavy");
    set_long("A circle of brass attached to a strong cord tied around a "+
        "brass hook.\n");

    add_prop(OBJ_I_VALUE, 250);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 450);
}
