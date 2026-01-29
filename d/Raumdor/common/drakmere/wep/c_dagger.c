inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */
/*     Modified:        Nerull, 2021, Updated with proper properties 
                        and hit/pen according to man weapon.      */

void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("slim");
    set_short("slim dagger");
    set_long("This is a slim, sharp dagger made of steel.\n");
    set_dt(W_SLASH);
    set_wt(W_KNIFE);
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20, 20) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(20, W_KNIFE) +
        random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
