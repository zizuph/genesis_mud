/*
  
  by Udana, /2006
*/

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 1.0
/* used to calculate value */
#define VALUE_MOD 1.1
#define AC 20
#define AT A_HEAD

inherit SILVER_DIR + "armour/colour_armour";

create_armour()
{
  set_name("helmet");
  add_name("helm");
  set_adj("round");
  set_short("round helmet");   
  set_long("A round steel helmet, painted in @@query_colour@@ and polished. It looks very sturdy.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC, AT, ({2, 4, -2}));
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
