/*
 * Tomb dweller helmet: base model = iron helmet
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
     set_short("iron helmet");
     set_long("It is a leather helmet with iron plates fastened "+
        "to it. It looks like it would provide decent "+
        "protection. It looks like the style worn by the tomb dwellers.\n");
     set_adj(({"iron", "iron-plated", "tomb", "dweller"}));
     set_default_armour(25, A_HEAD, 0, 0);
}
     
