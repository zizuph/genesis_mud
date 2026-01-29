inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
	set_name("knife");
	set_adj("small");
	add_adj("dirty");
	set_short("small dirty knife");
	set_pname("knives");
	set_long("The knife is dirty but under the dust you see a "
		+ "sharp blade.\n");
	set_hit(13);
	set_pen(12);
	set_wt(W_KNIFE);
	set_dt(W_IMPALE);
	set_hands(W_ANYH);

	add_prop(OBJ_I_VALUE, 40);
	add_prop(OBJ_I_WEIGHT, 300);
	add_prop(OBJ_I_VOLUME, 600);
}
