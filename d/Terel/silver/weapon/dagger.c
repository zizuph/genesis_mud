/*
  
  by Udana, /2006
*/

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume, 1.0 is for steel.*/
#define WEIGHT_MOD 0.9
/* used to calculate value */
#define VALUE_MOD 2.5
#define HIT 39
#define PEN 19


create_weapon()
{
  set_name("dagger");
  add_name("knife");
  set_adj("gold encrusted");
  add_adj("encrusted");
  set_short("encrusted dagger");   
  set_long("A long thin dagger, of perfect balance. The blade of this weapon have been encrusted with gold. "+
    "it's probably extremly valuable.\n");
  set_default_weapon(HIT, PEN, W_KNIFE,W_IMPALE, W_ANYH);
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
