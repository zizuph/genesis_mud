/*
 * Tomb dwellar helmet: top of the line model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("helmet");
     set_short("tempered helmet");
     set_long("A shiny tempered helmet used by tomb dwellers.\n");
     set_adj("shiny");
     set_adj("tempered");     

     set_default_armour(40, A_HEAD, 0, 0);
}
     
