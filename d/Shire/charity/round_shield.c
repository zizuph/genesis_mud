/*
 * Shield for charity box
 * Finwe, April 2004
 */

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

#define AC 10 + random(5)

create_armour()
{
    set_name("shield");
    add_name("_ch_round_shield_");
    set_short("round shield");
    set_long("This is a round shield. It is made from several thick " +
        "planks of wood and bound together with bands of steel.\n");
    set_ac(AC);
    set_at(A_SHIELD);
    set_am( ({ 2, -1, -1}) );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC,A_SHIELD) + 2800 );
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC) + random(101) - 100);
    add_prop(OBJ_I_VOLUME, 1000);
}
