/*
 * Shield for Svirfneblin
 * Finwe, July 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC 20 + random(5)

void create_faerun_armour()
{
    set_name("shield");
    set_short("round shield");
    set_long("This is a round shield. It is made from several thick " +
        "planks of wood and bound together with bands of steel.\n");
    set_ac(AC);
    set_at(A_SHIELD);
    set_am( ({ 0,0,0}) );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC,A_SHIELD) + 2800 );
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC) + random(101) - 100);
    add_prop(OBJ_I_VOLUME, 1000);
}
