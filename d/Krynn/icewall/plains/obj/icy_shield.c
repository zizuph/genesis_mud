/* Created by Macker 07/05/94 */
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Krynn/icewall/local.h"

inherit MELT_BASE


void
create_armour()
{
    set_name("shield");
	add_name("icy_shield");
	set_ac(18);
    set_at(A_SHIELD);
	set_am(({10, -4, -6}));
	add_adj("icy");
	set_short("icy shield");
	set_long("It is a shield made entirely of ice. It has a smooth " +
		"and round convex shape so that stabbing weapons will often " +
		"slip off the icy surface, deflecting the blow.\n");
	add_prop(OBJ_I_VOLUME, 700);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(14, A_SHIELD));
	/*Yes I know 14 != 18. I did this due to the fact that the shield is ma
	of ice, not metal. The ac is high because of it's slippery surface,
	rather than it's mass. */
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(18));
	make_me_meltable();
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

