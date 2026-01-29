/* A banana. ~solace/shaangsei/objects/banana */

inherit "/std/food";

#include "../defs.h"
#include "/sys/stdproperties.h"

void create_food()
{
    set_name("banana");
    set_adj("fresh");
    add_adj("yellow");
    set_long("A fresh yellow banana. It looks very appetising and you're "+
        "sure that it will taste very nice.\n");

    set_amount(20 + random(20));

    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 125);
}
