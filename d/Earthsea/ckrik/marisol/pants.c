/* Ckrik June 1998
 */

inherit "/d/Earthsea/std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 3

void
create_earthsea_armour()
{
  set_name("pants");
  set_pname("pantses");

  set_adj("old");
  set_adj("dirty");
  
  set_short("pair of dirty old pants");
  set_pshort("pairs of dirty old pants");

  set_long("A pair of dirty old pants. It is very well worn and beat up, " +
	   "but still very sturdy and useful.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_LEGS);
  set_am( ({0,0,0}) );
  
  add_prop(OBJ_I_WEIGHT, 1000 + random(25));
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
