/* Standard cloak for the guards in the jail of Tyr. */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
	set_name("cloak");
	set_short("yellow hide cloak");
	set_long("This cloak is made of mekillot hide, worked into a yellow "
		+"colour. Or it might have become yellow from all the sand "
		+"and dust that is in the air around Tyr, from where it "
		+"originate.\n");

	set_adj("yellow");
	add_adj("hide");

	set_ac(15);
	set_am(({ -1, 1, 0}));
	set_at(A_ROBE);

	add_prop(OBJ_I_WEIGHT, 4000);
	add_prop(OBJ_I_VOLUME, 2000);
}
