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
     set_short("steel chainmail");
     set_long("It is a chainmail made of steel links. The craftsmanship "+
         "is of good quality and looks like the style worn by tomb "+
         "dwellers.\n");
     set_adj(({"steel", "link", "tomb", "dweller" }));
	 add_item(({"steel links", "links"}), "They are links made of steel.\n");	 

     set_default_armour(30, A_BODY, 0, 0);
}
