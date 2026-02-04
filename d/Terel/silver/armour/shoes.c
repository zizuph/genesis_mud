/*
  
  by Udana, /2006
*/

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.2
/* used to calculate value */
#define VALUE_MOD 1.9
#define AC 8
#define AT A_FEET

create_armour()
{
  set_name("shoes");
  set_adj("elegant");
  set_short("pair of elegant shoes");
  set_pshort("pairs of elegant shoes");   
  set_long("A pair of elegant, expensive shoes. Footgear of this design are very trendy in Calathin this year.\n");
  set_default_armour(AC, AT, ({0, 0, 0}));
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
