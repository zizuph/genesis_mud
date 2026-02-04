/*
  
  by Udana, /2006
*/

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.6
/* used to calculate value */
#define VALUE_MOD 1.1
#define AC 9
#define AT A_ROBE

inherit SILVER_DIR + "armour/colour_armour";

create_armour()
{
  set_name("cloak");
  set_adj("heavy");
  set_short("@@query_colour@@ cloak");   
  set_long("A @@query_colour@@ cloak made of heavy cloth, improved with studded leather "+
    "around the shoulder area.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC, AT, ({-2, 2, 0}));
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
