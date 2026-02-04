/*
  
  by Udana, /2006
*/

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.9
/* used to calculate value */
#define VALUE_MOD 1.4
#define AC 32
#define AT (A_BODY | A_ARMS)


#ifndef OBJ_COLD_WEATHER_PROTECT
#define OBJ_COLD_WEATHER_PROTECT "_obj_cold_weather_protect"
#endif

inherit SILVER_DIR + "armour/colour_armour";

create_armour()
{
  set_name("chainmail");
  add_name("mail");
  set_adj("steel");
  set_short("@@query_colour@@ steel chainmail");   
  set_long("A mesh of small rings of tempered steel. It consist of a vest underlined with leather and sleeves. "+
    "The whole armour has been carefully covered with @@query_colour@@ paint.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC, AT, ({5, -1, 2}));
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
  
   add_prop(OBJ_COLD_WEATHER_PROTECT, 1);
}
