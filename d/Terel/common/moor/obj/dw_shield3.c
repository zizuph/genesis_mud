/*
 * Tomb dweller shield: good model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"shield"}));
     set_short("alloy shield");
     set_long("It is a shield cast from an unfamiliar alloy. "+
         "The craftsmanship looks good. This is the style "+
         "made by tomb dwellers.\n");
     set_adj(({"alloy", "metal", "tomb", "dweller" }));

     set_default_armour(29, A_SHIELD, 0, 0);
	 set_shield_slot(({ A_BODY, A_LEGS }));
}
