inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */
/*     Modified:        Nerull, 17/10-09 (increased hit/pen to 34)*/
/*     Modified:        Nerull, 2021, Updated with proper properties 
                        and hit/pen according to man weapon.      */

void
create_weapon()
{
    ::create_weapon();
    set_name("pike");
    set_adj("long");
    add_adj("deadly");
    set_short("long deadly pike");
    set_long("This pike has a wooden shaft, with a slim and sharp steel "+
    "blade. It looks like you could do some nice damage with it.\n");
    set_dt(W_IMPALE);
    set_wt(W_POLEARM);
    set_hit(35);
    set_pen(35);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_POLEARM) +
        random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
