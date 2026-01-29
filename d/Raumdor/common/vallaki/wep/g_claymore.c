inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */
/*     Modified:        Nerull, 17/10-09 (increased hit/pen to 40)*/

void
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    add_name("claymore");
    set_adj("silver");
    add_adj("shiny");
    set_short("shiny silver claymore");
    set_long("This huge claymore is made of shiny silver like steel. It is "+
    "strong and sharp. You see a golden cross embeded in the cross "+
    "piece. It is large, but well balanced.\n");
    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_SWORD);
    set_hit(40);
    set_pen(40);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,1000);
}
