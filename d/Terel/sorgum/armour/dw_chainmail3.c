/*
 * Tomb dweller chainmail: medium model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("chainmail");
     set_short("alloy chainmail");
     set_long("Its an alloy chainmail worn by tomb dwellers.\n");
     set_adj("alloy");

     set_default_armour(35, A_BODY, 0, 0);
}
