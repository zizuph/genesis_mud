#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name(({"boots", "pair of boots"}));
     set_pname(({"pairs of boots","armours"}));
     set_short("pair of iron boots");
     set_pshort("pairs of iron boots");
     set_long("Its a pair of iron boots used by tomb dwellers.\n");
     set_adj(({"iron"}));

     set_default_armour(25, A_FEET, 0, 0);
    }
