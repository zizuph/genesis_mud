inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <macros.h>

create_armour()
{
	set_name("helm");
	add_name("helmet");
	add_adj("visored");
	add_adj("battle-worn");
	set_short("battle-worn visored helm");
	set_long("This visored helmet, although marred by battle, still"+
	   " appears to be slightly useful.");

	set_ac(40);
        set_at(A_HEAD);
	set_am(({ 5, 0, -5}));

	add_prop(OBJ_I_VALUE, 1150);
	add_prop(OBJ_I_WEIGHT, 2700);
	add_prop(OBJ_I_VOLUME, 1600);
}

query_recover()
{
  return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
init_arm_recover(arg);
}
