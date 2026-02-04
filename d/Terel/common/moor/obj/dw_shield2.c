/*
 * Tomb dweller shield: medium model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"shield"}));
     set_short("steel shield");
     set_long("It is a shield cast from steel. The craftsmanship "+
         "is of good quality and looks like the style made by tomb "+
         "dwellers.\n");
     set_adj(({"steel", "tomb", "dweller", "metal" }));

     set_default_armour(24, A_SHIELD, 0, 0);
	 set_shield_slot(({ A_BODY, A_LEGS }));
}

