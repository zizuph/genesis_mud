/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/arm/
*   Modified by Meton - 2020
*   Eaten by wolves for loot.
*   Copied from:Kabals Nobles.
*
*/

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("high-heels");
    add_name("heels");
    set_adj("black");
    add_adj("high");
    set_short("pair of black high-heels");
    set_long("Made of black leather, these high heels are a symbol of "
        + "wealthy status.\n");
    set_ac(2);
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT,80);
    add_prop(OBJ_I_VOLUME,60);
}

