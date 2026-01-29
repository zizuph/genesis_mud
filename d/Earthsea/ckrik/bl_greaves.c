inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 35

void
create_armour()
{
  set_name("greaves");
  set_pname("greaveses");

  set_adj("blackened");
  
  set_short("pair of blackened greaves");
  set_pshort("pairs of blackened greaves");

  set_long("This pair of shin guards is standard issue for the" +
	   " castle guards. The polished bronze seems to shine" +
	   " in the sunlight. It seems well made and quite" +
	   " protective.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_LEGS);
  set_am( ({1,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 2500 + (random(25) -  10));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(25) - 10);

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
