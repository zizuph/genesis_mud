inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <macros.h>

create_armour()
{
	set_name("gauntlets");
	add_adj("bloodied");
	set_short("bloodied gauntlets");
	set_long("These gauntlets are very well used, probably by someone"+
	    " who dismembered people with his bare hands.\n");
	set_ac(30);
	set_at(A_HANDS | A_ARMS);
	set_am(({ 0, 7, -7}));
	add_prop(OBJ_I_VALUE, 800);
	add_prop(OBJ_I_WEIGHT, 1200);
	add_prop(OBJ_I_VOLUME, 400);
}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
  init_arm_recover(arg);
}
