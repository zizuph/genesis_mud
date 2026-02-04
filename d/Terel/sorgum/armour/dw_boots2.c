#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name(({"boots", "pair of boots"}));
     set_pname(({"pairs of boots","armours"}));
     set_short("pair of steel boots");
     set_pshort("pairs of steel boots");
     set_long("Its a pair of steel boots used by tomb dwellers.\n");
     set_adj(({"steel"}));

     set_default_armour(30, A_FEET, 0, 0);
    }
