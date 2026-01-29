inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("robe");
	set_short("dirty robe");
	add_adj("dirty");
	set_long("This robe is dirty from years of use by "+
	   "a dirty, smelly, slimy, slave who most likely "+
	   "lived in a place that made the sewer look "+
	   "desireable.\n");

	set_ac(5);
	set_at(A_ROBE);
	set_am(({ -3, -2, 5 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
