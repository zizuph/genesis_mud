#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_short("pair of tempered greaves");
     set_pshort("pairs of tempered greaves");
     set_long("Its a pair of tempered greaves used by tomb dwellers.\n");
     set_adj(({"tempered"}));

     set_default_armour(40, A_LEGS, 0, 0);
    }
