inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name(({ "helm", "helmet" }));
	set_short("iron pot helm");
	add_adj("iron");
	add_adj("pot");
	set_long("This is nothing more than an iron "+
	   "skull cap to protect the top of your head.\n");

	set_ac(15);
	set_at(A_HEAD);
	set_am(({ -7, -4, 11 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
