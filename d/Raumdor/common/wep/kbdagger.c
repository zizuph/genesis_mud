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
    set_long("This dagger, made of blackened steel, has a long, thin, razor-"+
    "sharp blade. The short hilt is wraped in black cloth, to give a better "+
    "grip on it. It looks very deadly.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_KNIFE);
    set_hit(16);
    set_pen(16);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,300);
}

