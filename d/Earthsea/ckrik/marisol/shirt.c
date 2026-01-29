/* Ckrik June 1998
 */

inherit "/d/Earthsea/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 3

void
create_earthsea_armour()
{
  set_name("shirt");
  set_pname("shirts");

  set_adj("blue");
  
  set_short("blue shirt");
  set_pshort("blue shirts");

  set_long("A goat herder's blue shirt.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_BODY);
  set_am( ({-1,-1,-1}) );
  
  add_prop(OBJ_I_WEIGHT, 500 + random(50));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(25));
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
