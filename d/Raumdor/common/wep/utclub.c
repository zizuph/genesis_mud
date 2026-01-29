inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* For use with the Undead Troll in Raumdor, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("club");
    set_adj("huge");
    add_adj("steel");
    set_short("huge steel club");
    set_long(
    "This is a large, hulking steel club. Its sleek design and great density"+
    " make this a powerful weapon.\n");
    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);
    set_hit(21);
    set_pen(28);
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,6000);
    add_prop(OBJ_I_VALUE,1000);
}

