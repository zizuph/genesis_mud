// A standard ringmail for the troll
// in Arnor
// Coded by Tigerlily, June 4, 2005

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>


void
create_armour()
{
    set_name("ring-mail");
    add_name(({ "mail", "ringmail", "ring mail" }));
    set_pname("ring-mails");
    add_pname("ringmails");
    add_pname("mails");
    set_adj("stout");
    add_adj("orc");
    set_short("stout ring-mail");
    set_long("This is a hard leather armour with steel rings sewn to it for "
      + "additional protection. It looks to be stoutly made.\n");

    set_default_armour(40, A_BODY, ({ -1, 2, -1 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40, A_BODY));
    add_prop(OBJ_I_VOLUME, 2315); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40)); 
}
