inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 33

void
create_armour()
{
  set_name("mask");
  set_pname("masks");

  set_adj("blackened");
  set_adj("face");

  set_short("blackened face mask");
  set_pshort("blackened face masks");

  set_long("A blackened face mask. This mask offers great " +
	   "protection. It not only covers the wearer's entire " +
	   "head, it also covers the wearer's neck.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_HEAD);
  set_am( ({-1,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 2000 + (random(250)));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

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

