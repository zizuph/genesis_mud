/*
  
  by Udana, /2006
*/

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.8
/* used to calculate value */
#define VALUE_MOD 1.2
#define AC 32
#define AT A_SHIELD

inherit SILVER_DIR + "armour/colour_armour";

create_armour()
{
    set_name("shield");
    set_adj("round");
    add_adj("wooden");
    set_short("round wooden shield");   
    set_long("A round wooden, painted in @@query_colour@@ and studded with steel. It looks very sturdy.\n");
    /* (impale, slash, bludgeon) */
    set_default_armour(AC, AT, ({2, -4, 4}));

    add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
    add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
    add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
