inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("guards");
	set_short("wooden leg guards");
	add_adj("wooden");
	add_adj("leg");
	set_long("They are wooden devices designed to protect the "+
	   "shins. Obviously, wood isn't that good, but they are better "+
	   "than nothing.\n");

	set_ac(15);
	set_at(A_LEGS);
	set_am(({ -10, 0, 10 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
