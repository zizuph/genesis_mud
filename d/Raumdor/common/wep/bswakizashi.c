inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* blue steel wakizashi, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("wakizashi");
    set_adj("steel");
    add_adj("blue");
    set_short("blue steel wakizashi");
    set_long("This slim, short sword has a blade made of razor-sharp, "+
    "blue tinted steel. It could cut through your flesh easily.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_hit(25);
    set_pen(30);
    add_prop(OBJ_I_WEIGHT,5100);
    add_prop(OBJ_I_VOLUME,3500);
    add_prop(OBJ_I_VALUE,800);
}

