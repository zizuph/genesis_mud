#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"boots", "pair of boots"}));
     set_pname(({"pairs of boots","armours"}));
     set_short("pair of steel alloy boots");
     set_pshort("pairs of steely alloy boots");
     set_long("It is a pair of leather boots cast from an unfamiliar "+
        "steel alloy. They look like they would provide decent "+
        "protection. These boots are worn by the tomb dwellers.\n");
     set_adj(({"alloy", "steel", "tomb", "dweller", "zombie"}));
     set_default_armour(30, A_FEET, 0, 0);
	 
    }
