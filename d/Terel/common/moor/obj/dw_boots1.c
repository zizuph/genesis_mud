#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"boots", "pair of boots"}));
     set_pname(({"pairs of boots","armours"}));
     set_short("pair of iron boots");
     set_pshort("pairs of iron boots");
     set_long("It is a pair of leather boots with iron plates fastened "+
        "to the top and sides. They look like they would provide decent "+
        "protection. These iron boots are worn by the tomb dwellers.\n");
     set_adj(({"iron", "iron-plated", "tomb", "dweller", "zombie"}));
     set_default_armour(20, A_FEET, 0, 0);
	 
    }
