inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
	set_name("club");
	set_short("blood-stained club");
	set_long(
		"This is truly the craftswork of the trolls, a rough spiked " +
        "club. It looks like it could smash rocks, and this might " +
        "be true. It is covered with old blood and guts hanging from it.\n");
	set_adj("huge");
	
	set_hit(39);
	set_pen(35);
	
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON | W_SLASH );
	
	set_hands(W_ANYH);
	
	add_prop(OBJ_I_WEIGHT, 20000);
	add_prop(OBJ_I_VOLUME, 12000);
}	
	