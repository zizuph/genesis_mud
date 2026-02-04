/*
 * Tomb dweller chainmail: base model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name("chainmail");
     set_short("iron chainmail");
     set_long("It is a chainmail made of iron links. The craftsmanship "+
         "is of decent quality and looks like the style worn by tomb "+
         "dwellers.\n");
     set_adj(({"iron", "link", "tomb", "dweller" }));
	 add_item(({"iron links", "links"}), "They are links made of iron.\n");

     set_default_armour(25, A_BODY, 0, 0);
}
