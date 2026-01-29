inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("fine");
    add_adj("steel");
    add_adj("chain");
    set_short("pair of fine steel chain greaves");
    set_pshort("pairs of fine steel chain greaves");
    set_long("Made of very fine steel, these pair of chain greaves "+
    "have metal plates at the knees. The rest is made of very fine "+
    "chain links that run from your hips, down to your ankles.\n");
    set_ac(27); /* +2 because of the fine steel it is made of */
    set_am(({-2,3,-1}));
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,5700);
    add_prop(OBJ_I_VOLUME,4000);
}

