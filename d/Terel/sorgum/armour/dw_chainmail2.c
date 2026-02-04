/*
 * Tomb dweller chainmail: base model
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("chainmail");
     set_short("steel chainmail");
     set_long("Its steel chainmail worn by tomb dwellers.\n");
     set_adj("steel");

     set_default_armour(30, A_BODY, 0, 0);
}
