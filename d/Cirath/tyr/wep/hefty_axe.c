inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
	set_name("axe");
	set_short("hefty steel axe");
	set_long("This axe is of very good quality. Fine balance and a "
		+"polished handle made of some sort of wood. The edge of this "
		+"axe is unusually broad. The broad edge will make this axe "
		+"hit deeper and harder than other common weapons.\n");

	set_adj  ("hefty");
	add_adj  ("steel");

	set_hit(25);
	set_pen(30);

	set_wt(W_AXE);
	set_dt(W_SLASH | W_BLUDGEON);
	set_hands(W_ANYH);
	add_prop(OBJ_I_WEIGHT,6000);
	add_prop(OBJ_I_VOLUME,1000);
}
