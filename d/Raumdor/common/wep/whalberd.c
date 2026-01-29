inherit "/std/weapon";
#include "/d/Raumdor/defs.h"

void
create_weapon()
{
    ::create_weapon();
    set_name("halberd");
    set_adj(({"steel","black"}));
    set_short("black steel halberd");
    set_long(
    "This is a long wood and steel staff with a large, razor sharp "+
    "black blade at its top. A short chain hangs from the back of the "+
    "black, where a small, grim black skull is attached.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_hit(35+random(3));
    set_pen(27+random(3));
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_VALUE,300);
}

