#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("shield");
    set_short("very large shield");
    set_adj("huge");
    set_long("This shield is enormous. It's atleast 2 meters in diameter\n"+
	     "and must weigh something like 100 - 150 kilos. It's made\n"+
	     "of oak with heavy iron reinforcements.\n");
    
    set_default_armour(25, A_SHIELD, 0, 0);

    set_shield_slot(({ A_L_ARM, A_BODY }));   /* Covers what? */
}
