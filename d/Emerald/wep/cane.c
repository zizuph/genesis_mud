inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h" 

void
create_weapon()
{
	set_name("cane");
	set_short("wooden cane");
	set_long("This is an old wooden cane.\n");
	set_adj("wooden");

	set_hit(8);
	set_pen(7);

	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);

	set_hands(W_ANYH);

	add_prop(OBJ_I_WEIGHT, 750);
	add_prop(OBJ_I_VOLUME, 500);
}
