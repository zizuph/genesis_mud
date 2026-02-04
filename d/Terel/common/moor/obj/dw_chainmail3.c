/*
 * Tomb dweller chainmail: medium model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name("chainmail");
     set_short("alloy chainmail");
     set_adj("alloy");
     set_long("It is a chainmail with links made of an unfamiliar alloy. "+
         "The craftsmanship looks good. This is the style worn by tomb "+
         "dwellers.\n");
     set_adj(({"alloy", "metal", "link", "tomb", "dweller" }));
	 add_item(({"alloy links", "links"}), "They are links made of an odd alloy.\n");	 
     set_default_armour(35, A_BODY, 0, 0);
}
