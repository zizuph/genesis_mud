/*
  
  by Udana, /2006
*/

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 1.1
/* used to calculate value */
#define VALUE_MOD 1.5
#define AC 32
#define AT A_LEGS

inherit SILVER_DIR + "armour/colour_armour";

create_armour()
{
  set_name("greaves");
  add_name("half-greaves");
  set_adj("steel");
  set_short("pair of @@query_colour@@ half-greaves");
  set_pshort("pairs of steel half-greaves");
  set_long("Two plates of thick, @@query_colour@@ steel with few straps attached to them. They look "+
    "like they could offer some reasonable protection for your shins.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC, AT, ({-2, 0, 1}));
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_ARMOUR(AC)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_ARMOUR(AC, AT)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
