inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("chainmail");
    add_name("mail");
    set_adj("fine");
    add_adj("steel");
    set_short("fine steel chainmail");
    set_long("This is a very fine suit of chainmail. It looks very well "+
    "crafted, and made from a very pure steel. The emblem of the High "+
    "Lord of Kabal is emblazed on it.\n");
    set_ac(27); /* +2 because of the fine steel it is made of */
    set_am( ({ -2, 3, -1 }) );
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,7600);
    add_prop(OBJ_I_VOLUME,5000);
}

