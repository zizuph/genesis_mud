#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_short("pair of alloy greaves");
     set_pshort("pairs of alloy greaves");
     set_long("Its a pair of alloy greaves used by tomb dwellers.\n");
     set_adj(({"alloy"}));

     set_default_armour(35, A_LEGS, 0, 0);
    }
