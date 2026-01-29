inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
	set_name("sword");
	set_short("double-edged sword");
	set_long("This sword has an edge on both sides of the blade. The edge "
		+"the one of the sides is very sharp, while the edge on the "
		+"other side is somewhat serrated. If you are good enough you "
		+"will find this weapon excellent, to combine the two "
		+"different edges.\n");

	set_adj  ("double-edged");

	set_hit(30);
	set_pen(25);

	set_wt(W_SWORD);
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_RIGHT);
	add_prop(OBJ_I_WEIGHT,5000);
	add_prop(OBJ_I_VOLUME,3000);
}
