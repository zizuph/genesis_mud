/*
 * PLatemail for Skeleton
 * --Finwe, July 2006
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

void create_faerun_armour()
{
    set_name("platemail");
    set_adj(({"steel", "dented"}));
    set_short("dented steel platemail");
    set_long("This "+short()+" consists of small metal plates fixed " +
        "In ridges to provide mobility and protection. The mail look" +
        "s rusted and stiff, as if it care was not a priority for its" +
        " user. It looks like it would protect you well enough.\n");
 
    set_at(A_TORSO);
    set_ac(30);
    set_am(({-2, 3, -1}));
/*
    add_prop(OBJ_I_VALUE,1200);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_WEIGHT,2500);
*/

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));

}
