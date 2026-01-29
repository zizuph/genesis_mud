/* Basic weapon file ready for editing

*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
	set_name("club");
	set_long(
		"A black club used by the clerics of the Emerald.\n");
	set_adj("black");

	set_hit(35);
	set_pen(35);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_RIGHT);
}
