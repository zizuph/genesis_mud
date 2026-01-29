inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("shirt");
	set_short("rugged burlap shirt");
	add_adj("rugged");
	add_adj("burlap");
	set_long("It is a very uncomfortable shirt that itches if "+
	   "you wear it. It is strong, though and is good for "+
	   "making sacks to hold potatoes. Usually, only the poor "+
	   "wear burlap clothes.\n");

	set_ac(12);
	set_at(A_BODY);
	set_am(({ -5, 2, 3 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
