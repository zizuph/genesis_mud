inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* black wooden club, by Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("club");
    set_adj("wooden");
    add_adj("black");
    set_long(
    "This wooden club is made of black oak. You don't want to be at the\n"+
    "other end of this club when it is being swung.\n");
    set_hit(24);
    set_pen(28);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_VALUE,700);
}

 
