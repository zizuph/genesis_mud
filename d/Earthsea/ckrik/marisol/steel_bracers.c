inherit "/d/Earthsea/std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 27

void
create_earthsea_armour()
{
  set_name("bracer");
  set_pname("bracers");

  set_adj("steel");
  set_adj("alloy");
  
  set_short("pair of steel alloy bracers");
  set_pshort("pairs of steel alloy bracers");

  set_long("A pair of steel alloy bracers. Made from strong " +
	   "steel alloys, these bracers offer excellent protection " +
	   "to one's arms.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_ARMS);
  set_am( ({-2,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 3000 + random(250));
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
