inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 23

void
create_armour()
{
  set_name("helmet");
  set_pname("helmets");

  set_adj("shiny");
  set_adj("bronze");
  
  set_short("shiny bronze helmet");
  set_pshort("shiny bronze helmets");

  set_long("This helmet is standard issue for the castle guards." +
	   " On the top of the helmet, it is decorated by" +
	   " a plume of fluffy white feathers. It is well" +
	   " constructed and offer good protection for" +
	   " the wearer's head.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_HEAD);
  set_am( ({-1,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 2000 + (random(50) -  25));
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

