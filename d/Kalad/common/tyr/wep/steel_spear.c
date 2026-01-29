inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
        ::create_weapon();
	set_name("spear");
	set_short("long steel spear");
	set_long("This is a long spear that must be handled with care so "
		+"that none will get hurt. The blade in the top is made of "
		+"steel and it is sharpened so the edge reflects the light. "
		+"In the hands of competent fighter this will be a lethal "
		+"weapon.\n");

	set_adj  ("long");
	add_adj  ("steel");

	set_hit(30);
	set_pen(30);

	set_wt(W_POLEARM);
	set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
	set_hands(W_BOTH);
	add_prop(OBJ_I_WEIGHT,10000);
	add_prop(OBJ_I_VOLUME,5000);
}
