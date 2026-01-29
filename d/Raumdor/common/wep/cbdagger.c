inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Black steel dagger, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("black");
    add_adj("steel");
    set_short("black steel dagger");
    set_long("This dagger, made of blackened steel, has a chipped and "+
    "rusty blade. It looks old and used, but still able to do some "+
    "damage.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_KNIFE);
    set_hit(15);
    set_pen(15);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,100);
}

