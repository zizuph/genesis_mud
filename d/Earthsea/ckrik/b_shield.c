inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 25

void
create_armour()
{
  set_name("shield");
  set_pname("shields");

  set_adj("shiny");
  set_adj("bronze");
  
  set_short("shiny bronze shield");
  set_pshort("shiny bronze shields");

  set_long("This shield is standard issue for the castle guards." +
	   " It is a sturdy metal plate, molded to and reinforced" +
	   " by a solidly constructed frame. It is a bit heavy," +
	   " but not too bad for the protection it offers. The" +
	   " shield can probably take a lot of punishment.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_SHIELD);
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
