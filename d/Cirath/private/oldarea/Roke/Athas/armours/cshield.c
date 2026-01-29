inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("shield");
	set_short("copper shield");
	add_adj("copper");
	set_long("It is made from nice, shiny copper.\n");

	set_ac(8);
	set_at(A_SHIELD);
	set_am(({ -2, 1, 1 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
