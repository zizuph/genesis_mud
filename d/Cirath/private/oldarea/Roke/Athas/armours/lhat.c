inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("hat");
	set_short("green leather hat");
	add_adj("green");
	add_adj("leather");
	set_long("This is a nice hat made from a the skin of a deer. "+
	  "It is made with a lovely green and set off by yellow trim.\n");

	set_ac(7);
	set_at(A_HEAD);
	set_am(({ -2, -2, 4 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
