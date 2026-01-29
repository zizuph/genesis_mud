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
    add_adj("blue");
    set_short("blue steel katana");
    set_long("This katana is made out of very fine steel that has a blue "+
    "tint to it at the edge of its blade. The handle is wraped in black "+
    "cloth. It still looks like a very "+
    "powerful weapon. The blade gleams in the light, and an inner "+
    "power radiates out of it.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_hit(35);
    set_pen(33);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,1000);
}

