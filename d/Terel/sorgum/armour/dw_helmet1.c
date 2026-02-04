/*
 * Tomb dweller helmet: base model = iron helmet
 *
 * based on code from the legion of darkness
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

create_terel_armour()
{
     set_name("helmet");
     set_short("iron helmet");
     set_long("iron helmet worn by tomb dwellers.\n");
     set_adj("iron");

     set_default_armour(25, A_HEAD, 0, 0);
}
     
