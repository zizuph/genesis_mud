/*
  
  by Udana, /2006
*/

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
/* used to calculate weight and volume*/
#define WEIGHT_MOD 1.1
/* used to calculate value */
#define VALUE_MOD 1.2
#define HIT 35
#define PEN 32


create_weapon()
{
  set_name("broadsword");
  add_name("sword");
  set_adj("broad");
  add_adj("steel");
  set_short("steel broadsword");   
  set_long("A sharp sword made of high-quality steel. It's quite heavy but well balanced, " +
    "and very sharp.\n");
  set_default_weapon(HIT, PEN, W_SWORD,W_IMPALE | W_SLASH, W_ANYH);
  
  add_prop(OBJ_I_VALUE, ftoi(itof(F_VALUE_WEAPON(HIT, PEN)) * VALUE_MOD));
  add_prop(OBJ_I_WEIGHT, ftoi(itof(F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD)) * WEIGHT_MOD));
  add_prop(OBJ_I_VOLUME, ftoi(itof(query_prop(OBJ_I_WEIGHT)) / (5.0 * WEIGHT_MOD)));
}
