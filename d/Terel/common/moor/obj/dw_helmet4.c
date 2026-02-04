/*
 * Tomb dwellar helmet: top of the line model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name("helmet");
     set_short("shiny tempered helmet");
     set_long("It is a shiny helmet cast with an iron alloy that "+
        "has been tempered to give it greater impact resistance "+
        "than normal steel. The craftsmanship is "+
        "characteristic of the tomb dwellers.\n");
     set_adj("tempered");
     add_adj(({"shiny", "alloy", "metal", "tomb", "dweller"}));

     set_default_armour(40, A_HEAD, 0, 0);
}
     
