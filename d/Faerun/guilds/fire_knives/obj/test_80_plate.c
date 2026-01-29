/*
*
 */
#include "/d/Faerun/defs.h"
#include "/d/Faerun/mere/arm/defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC 80

void create_faerun_armour()
{
    set_name("platemail");
    set_adj(({"plain", "ribbed"}));
    set_short("plain ribbed platemail");
    set_long("This "+short()+" is made of steel plates that overlay " +
        "each other. The armour was forged ages ago by long forgotten " +
        "blacksmiths. Each plate is ribbed and designed to deflect " +
        "blows during battle.\n");
 
    set_at(A_BODY);
    set_ac(AC);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, 2500 + random(250));
}
