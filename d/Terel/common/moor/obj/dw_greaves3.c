#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_short("pair of alloy greaves");
     set_pshort("pairs of alloy greaves");
     set_long("It is a pair of alloy greaves designed to handle "+
         "impact during battle with less chance of breaking than "+
         "pure iron. The craftsmanship looks quite good. This is "+
		 "the style worn by tomb dwellers.\n");	 
     set_adj(({"alloy", "tomb", "dweller" }));
     set_default_armour(35, A_LEGS, 0, 0);
}
