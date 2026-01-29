/* legs_lth: Leather boots to keep the feet safe. */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("boots");
    set_short("pair of hard leather boots");
    set_pshort("pairs of hard leather boots");
    set_long("These sturdy workman's boots protect not only the feet but "+
             "most of the leg as well.\n");
    set_adj("hard");
    add_adj("leather");

    set_ac(10);
    set_am(({ -1, 0, 1}));
    set_at(A_LEGS);

    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 900);
}
