inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name(({ "armbands", "bands" }));
	set_short("bronze armbands");
	add_adj("bronze");
	add_adj("arm");
	set_long("They fit tightly over the upper arm to give you "+
	   "more protection on those bad days when parrying just "+
	   "doesn't seem to work.\n");

	set_ac(25);
	set_at(A_ARMS);
	set_am(({ 2, 5, -7 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
