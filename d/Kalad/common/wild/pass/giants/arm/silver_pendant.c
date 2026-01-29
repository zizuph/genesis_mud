/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/arm/
*   Modified by Meton - 2020
*   Eaten by wolves for loot.
*   Copied from Kabals Nobles.
*/

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("pendant");
    set_adj("silver");
    set_short("silver pendant");
    set_long("This pendant is made of solid silver, and hangs on "
        + "a silver chain. In the center of the pendant is a very small, "
        + "but expensive looking ruby.\n");
    set_ac(0);
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,90);
    add_prop(OBJ_I_VOLUME,60);
    add_prop(OBJ_I_VALUE,370);
}

