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
#define VALUE_MOD 2.3
#define AC 7
#define AT A_ROBE

create_armour()
{
  set_name("robe");
  set_adj("expensive");
  add_adj("merchant");
  set_short("expensive robe");   
  set_long("A soft, colourfull robe, is a perfect outfit for a prosperous merchant.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC, AT, ({0, 0, 0}));
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
