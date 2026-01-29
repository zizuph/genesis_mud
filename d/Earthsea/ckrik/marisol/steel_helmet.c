inherit "/d/Earthsea/std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 30

void
create_earthsea_armour()
{
  set_name("helmet");
  set_pname("helmets");

  set_adj("steel");
  set_adj("alloy");
  
  set_short("steel alloy helmet");
  set_pshort("steel alloy helmets");

  set_long("A steel alloy helmet. Made from the finest and strongest " +
	   "alloy steel, it provides great protection to its wearer's " +
	   "head.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_HEAD);
  set_am( ({-2,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 2500 + random(200));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(100));

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
