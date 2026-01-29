inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("shield");
	set_short("huge steal shield");
	add_adj("huge");
	add_adj("steel");
	set_long("This is a very large shield made from "+
	   "high quality steel. It appears to be quite "+
	   "useful.\n");

	set_ac(40);
	set_at(A_SHIELD);
	set_am(({ -5, 3, 2 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
