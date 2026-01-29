inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("polished");
    add_adj("augmented");
    set_short("pair polished augmented greaves");
    set_long("These greaves are very protective, as well as comfortable."+
    " However, they are quite heavy.\n");
    set_ac(34); 
    set_am(({-1,1,0}));
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,6300);
    add_prop(OBJ_I_VOLUME,5000);
}

