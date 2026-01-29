/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/arm/
*   Modified by Meton - 2020
*   Eaten by wolves for loot.
*   Copied from:Kabals Nobles
*
*/

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("chain");
    set_adj("gold");
    set_short("gold chain");
    set_long("This is a chain of rings made of solid gold! It is heavy "
        + "and very valuable looking.\n");
    set_ac(0);
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,90);
    add_prop(OBJ_I_VOLUME,60);
    add_prop(OBJ_I_VALUE,425);
}

