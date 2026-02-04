/*
 * Tomb dweller helmet: medium model
 *
 * based on code from the legion of darkness
 */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name("helmet");
     set_short("steel helmet");
     set_long("It is a helmet cast from steel. The craftsmanship "+
         "is of good quality and looks like the style worn by tomb "+
         "dwellers.\n");
     set_adj(({"steel", "tomb", "dweller" }));
     set_default_armour(30, A_HEAD, 0, 0);
}
     
