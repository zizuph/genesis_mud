#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
	set_name("staff");
 	set_short("strange staff");
	set_long("This is a strange staff with a miniature dragon at the top." +
		"It feels rather massive, and you think it probably could crack a " +
		"skull or two.\n");
	set_hit(30);
	set_pen(25);
	set_wt(W_POLEARM);
	set_dt((W_BLUDGEON));
	set_hands(W_BOTH);
	add_prop(OBJ_I_WEIGHT,20000);
	add_prop(OBJ_I_VOLUME,5000);
 	add_prop(OBJ_I_VALUE,900);
}
