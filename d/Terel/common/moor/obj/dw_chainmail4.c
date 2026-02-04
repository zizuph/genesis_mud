/*
 * Tomb dweller chainmail: top of line model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name("chainmail");
     set_short("shiny tempered chainmail");
     set_long("It is a shiny chainmail made of links of an iron alloy that "+
        "has been tempered to give it greater impact resistance than normal "+
		"steel. The craftsmanship is "+
        "characteristic of the tomb dwellers.\n");
     set_adj("tempered");
     add_adj(({"shiny", "alloy", "metal", "tomb", "dweller"}));
	 add_item(({"shiny links", "links"}), "They are links made of a shiny metal.\n");	 
     set_default_armour(40, A_BODY, 0, 0);
}
