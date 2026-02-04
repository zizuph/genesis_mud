/*
 * Tomb dweller chainmail: base model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("chainmail");
     set_short("iron chainmail");
     set_long("Its an iron chainmail worn by tomb dwellers.\n");
     set_adj("iron");

     set_default_armour(25, A_BODY, 0, 0);
}
