inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* For use with the Death Mage in Raumdor, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("staff");
    set_adj("black");
    add_adj("wooden");
    set_short("black wooden staff");
    set_long(
    "A long, sleek light staff made of solid oak wood that looks "+
    "like it can do some good damage. At its tip, a small grim "+
    "skull is carved in.\n");
    set_dt(W_BLUDGEON);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_hit(33+random(3));
    set_pen(21+random(3));
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_VALUE,300);
}

