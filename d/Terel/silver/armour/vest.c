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
#define WEIGHT_MOD 0.5
/* used to calculate value */
#define VALUE_MOD 0.9
#define AC 18
#define AT A_BODY

create_armour()
{
  set_name("vest");
  set_adj("leather");
  set_short("leather vest");   
  set_long("A vest of hardened leather. It's rather typical cloath for a commoner who spends "+
    "a lot of time outdoors.\n");
  set_default_armour(AC, AT, ({-2, 2, 0}));
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
