inherit "std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

void create_weapon()
{
	set_name("club");
	set_short("wooden club");
	set_long("This is an old well used, wooden club.\n");
	set_adj("wooden");
	
	set_hit(15);
	set_pen(12);

	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);

	set_hands(W_ANYH);

	add_prop(OBJ_I_WEIGHT, 3500);
	add_prop(OBJ_I_VOLUME, 5000);
}

