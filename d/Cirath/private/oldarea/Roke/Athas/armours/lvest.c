inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("vest");
	set_short("leather vest");
	add_adj("leather");
	set_long("This is a leather vest used as protection against "+
	   "blunt objects. It doesn't smell very good, but then again "+
	   "it may save your life.\n");

	set_ac(20);
	set_at(A_BODY);
	set_am(({ -10, -10, 20 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
