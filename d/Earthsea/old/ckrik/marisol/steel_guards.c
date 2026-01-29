inherit "/d/Earthsea/std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 30

void
create_earthsea_armour()
{
  set_name("guards");
  set_pname("guardses");

  set_adj("steel");
  set_adj("shin");
  
  set_short("pair of steel shin guards");
  set_pshort("pairs of steel shin guards");

  set_long("A pair of steel shin guards. It seems well made and quite" +
	   " protective. It should protect its wearer's legs well.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_LEGS);
  set_am( ({-2,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 3500 + random(500));
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
