inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>

create_armour()
{
	set_name("boots");
	set_short("high black boots");
	add_adj("high");
	add_adj("black");
	set_long("This is a fine pair of boots. They are hard soled, "+
	   "and high enough to reach the knee of a human, the upper thigh "+
	   "of a dwarf, and the armpits of a hobbit.\n");

	set_ac(27);
	set_at(A_FEET | A_LEGS);
	set_am(({ 2, -5, 3 }));

}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
