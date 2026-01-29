inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */
/*     Modified:        Nerull, 17/10-09 (increased hit/pen to 34)*/

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
    set_hit(40);
    set_pen(40);
   add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,900+random(200));
}
