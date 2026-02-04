/*
 * Tomb dweller helmet: good model
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
     set_short("alloy helmet");
     set_long("It is a helmet cast from an unfamiliar alloy. "+
         "The craftsmanship looks good. This is the style "+
         "worn by tomb dwellers.\n");
     set_adj(({"alloy", "metal", "tomb", "dweller" }));

     set_default_armour(35, A_HEAD, 0, 0);
}
     
     
