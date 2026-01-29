inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 40

void
create_armour()
{
  set_name("platemail");
  set_pname("platemails");

  set_adj("shiny");
  set_adj("bronze");
  
  set_short("shiny bronze platemail");
  set_pshort("shiny bronze platemails");

  set_long("This platemail is standard issue for the castle guards." +
	   " It has been polished and brightened to reveal the shining" +
	   " colour of the bronze. It is made of many plates that" +
	   " overlap each other, covering a inner lining of chainmail." +
	   " It is well constructed and it seems to be able to offer a" +
	   " great deal of protection to its wearer.\n");

  set_ac(ARMOUR_CLASS);
  set_at(A_BODY);
  set_am( ({-1,0,1}) );
  
  add_prop(OBJ_I_WEIGHT, 9600 + (random(50) -  25));
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
