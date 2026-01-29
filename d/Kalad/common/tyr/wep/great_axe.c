/* great_axe.c */

inherit "/d/Kalad/std/weapon";
#include <wa_types.h>
#include "defs.h"

void create_weapon()
{
        ::create_weapon();
	set_name("axe");
	set_short("great steel axe");
	set_long("You can feel the balance in this axe, though it takes two "
		+"hands to controll it. It is quite heavy but in the right "
		+"hands it will be a deadly weapon. The handle is covered "
		+"with blood stains, many innocent people must have been "
		+"slayed by this weapon.\n");

	set_adj  ("great");
	add_adj  ("steel");

	set_hit(35);
	set_pen(35);

	set_wt(W_AXE);
	set_dt(W_SLASH | W_BLUDGEON);
	set_hands(W_BOTH);
	add_prop(OBJ_I_WEIGHT,8000);
	add_prop(OBJ_I_VOLUME,1200);
}
