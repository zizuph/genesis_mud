inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */
/*     Modified:        Nerull, 2021, Updated with proper properties 
                        and hit/pen according to man weapon.      */

void
create_weapon()
{
    ::create_weapon();
    set_name("pike");
    set_adj("silver-edged");
    set_short("silver-edged pike");
    set_long("This pike has a long wooden haft, with a large, silvery "+
    "blade on the top.\n");
    set_dt(W_IMPALE);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 40) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM) +
        random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
