/* legs_lth: Leather boots to keep the feet safe. 
    Modified by Mirands - May 22, 2020 to fix the fact
    they aren't actually worn on the feet! Now worn on
    feet and legs.*/
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("boots");
    set_short("pair of hard leather boots");
    set_pshort("pairs of hard leather boots");
    set_long("These sturdy workman's boots protect not only the feet but "+
             "most of the leg as well.\n");
    set_adj("hard");
    add_adj("leather");

    set_ac(10);
    set_am(({ -1, 0, 1}));
    set_at(A_FEET | A_LEGS);

    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 900);
}
