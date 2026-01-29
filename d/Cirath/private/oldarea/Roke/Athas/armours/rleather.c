inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name(({ "breastplate", "plate" }));
	set_short("rigid leather breastplate");
	add_adj("rigid");
	add_adj("leather");
	add_adj("breast");
	set_long("This is made from hardened leather to protect your "+
	  "body from harmful objects, such as swords, and clubs.\n");

	set_ac(28);
	set_at(A_BODY);
	set_am(({ 0, 0, 0 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
