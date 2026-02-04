#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_short("pair of shiny tempered greaves");
     set_pshort("pairs of shiny tempered greaves");
     set_long("It is a pair of shiny tempered greaves made of "+
        "an iron alloy that has been tempered to give it greater "+
        "impact resistance than normal steel. The craftsmanship is "+
        "characteristic of the tomb dwellers.\n");
     set_adj(({"tempered", "shiny", "tomb", "dweller"}));
     set_default_armour(40, A_LEGS, 0, 0);
}
