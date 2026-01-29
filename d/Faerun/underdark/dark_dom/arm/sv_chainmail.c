/*
 * Chainmail for Svirfneblin
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
    set_name("chainmail");
    set_adj(({"steel", "small"}));
    set_short("small steel chainmail");
    set_long("This "+short()+" consists of small metal rings linked " +
        "together in a pattern to form a mesh. The chainmail looks " +
        "flexible but strong and was forged by svirfnebli. It looks " +
        "like it will protect you well in battle.\n");
 
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
