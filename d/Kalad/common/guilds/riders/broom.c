inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
void
create_weapon()
{
    ::create_weapon();
    set_name("broomj");
    set_adj("old");
    add_adj("rickety");
    set_short("rickety old broom");
    set_long("This is a rickety old broom, good for cleaning.\n");
    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);
    set_hit(5);
    set_pen(5);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,10);
}