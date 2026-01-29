inherit "/std/food";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
void
create_food()
{
    set_name("pie");
    add_name("fresh-baked_pie");
    set_adj("fresh-baked");
    set_short("fresh-baked pie");
    set_long("A wonderful smelling pie that looks like it was fresh from the "+
      "oven.\n");
    set_amount(250);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,250);
    add_prop(OBJ_I_VALUE,50);
}
