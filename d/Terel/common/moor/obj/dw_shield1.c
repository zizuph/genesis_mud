/*
 * Tomb dweller shield: base model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"shield"}));
     set_short("iron shield");
     set_long("It is a heavy iron shield used by tomb dwellers.\n");
     set_adj(({"iron", "tomb", "dweller"}));

     set_default_armour(19, A_SHIELD, 0, 0);
	 set_shield_slot(({ A_BODY, A_LEGS }));
}

