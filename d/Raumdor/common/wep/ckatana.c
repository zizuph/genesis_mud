inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* blue steel katana, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("katana");
    add_name("sword");
    set_adj("steel");
    add_adj("rusty");
    set_short("rusty steel katana");
    set_long("This katana looks like it was once made out of the "+
    "finest steel. Although it is now corroded and old, it still "+
    "looks like it can do some damage.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_hit(25);
    set_pen(25);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,500);
}

