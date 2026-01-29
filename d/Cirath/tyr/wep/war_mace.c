inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

void create_weapon()
{
	set_name("mace");
	set_short("big war mace");
	set_long("The mace have a winged head that will crush the body of "
		+"your enemy when you hit him with it. The handle is made of "
		+"wood while the winged head is forged of steel. The head "
		+"also have a sharp peak on the end of the handle that will "
		+"punch through your enemy's armour.\n");

	set_adj  ("big");
	set_adj  ("war");

	set_hit(30);
	set_pen(30);

	set_wt(W_CLUB);
	set_dt(W_IMPALE | W_BLUDGEON);
	set_hands(W_RIGHT);
	add_prop(OBJ_I_WEIGHT,7000);
	add_prop(OBJ_I_VOLUME,4000);
}
