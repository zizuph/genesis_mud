/*
  caravan guard and coachman boots
  by Udana, /2006
*/

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.5
/* used to calculate value */
#define VALUE_MOD 1.3
#define AC 12
#define AT A_FEET

#ifndef OBJ_COLD_WEATHER_PROTECT
#define OBJ_COLD_WEATHER_PROTECT "_obj_cold_weather_protect"
#endif

create_armour()
{
  set_name("boots");
  set_adj("high");
  add_adj("leather");
  set_short("pair of high leather boots");
  set_pshort("pairs of high leather boots");   
  set_long("A knee high leather boots, looking quite comfortable. A perfect choice for someone who "+
    "travels a lot.\n");
  set_default_armour(AC, AT, ({-1, 3, -1}));
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
  
   add_prop(OBJ_COLD_WEATHER_PROTECT, 1);
}
