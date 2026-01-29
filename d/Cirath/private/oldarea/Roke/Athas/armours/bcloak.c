inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("cloak");
	set_short("long billowing cloak");
	add_adj("long");
	add_adj("billowing");
	set_long("A very long, elegant cloak. Clearly a sign of "+
	   "prestige and power.\n");

	set_ac(19);
	set_at(A_ROBE);
	set_am(({ -3, 4, -1 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
