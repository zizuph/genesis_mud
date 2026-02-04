/*
 * Tomb dweller chainmail: medium model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("chainmail");
     set_short("tempered chainmail");
     set_long("Its a shiny tempered chainmail worn by tomb dwellers.\n");
     set_adj("tempered");
     add_adj("shiny");
     set_default_armour(40, A_BODY, 0, 0);
}
