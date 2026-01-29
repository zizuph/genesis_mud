inherit "/std/food";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
void
create_food()
{
    set_name("pear");
    set_adj("green");
    set_short("green pear");
    set_long("A juicy green pear.\n");
    set_amount(50);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,75);
    add_prop(OBJ_I_VALUE, 10);
}
