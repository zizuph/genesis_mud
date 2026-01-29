inherit "/d/Earthsea/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 37

void
create_earthsea_armour()
{
  set_name("armour");
  set_pname("armours");

  set_adj("steel");
  set_adj("plated");
  
  set_short("steel plated armour");
  set_pshort("steel plated armours");

  set_long("A steel plated armour of excellent quality. " +
	   "Constructed from the best alloy steels, this armour " +
	   "provides great protection to its wearer. The breast " +
	   "plates of the armour conform to the pectorial muscle " +
	   "of the wearer, enhancing the looks of the wearer.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_BODY);
  set_am( ({-3,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 12000 + random(1000));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(150));
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
