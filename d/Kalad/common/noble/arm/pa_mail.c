inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("mail");
    set_adj("polished");
    add_adj("augmented");
    set_short("polished augmented mail");
    set_long("This suit of armour is made of fine steel and leather. "+
    "You feel quite protected, if a bit heavy.\n");
    set_ac(34); 
    set_am(({-1,1,0}));
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,8400);
    add_prop(OBJ_I_VOLUME,7000);
}

