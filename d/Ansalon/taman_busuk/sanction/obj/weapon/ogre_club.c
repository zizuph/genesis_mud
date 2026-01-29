inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("mace");
    set_adj("heavy");
    add_adj("steel");
    set_short("heavy steel mace");
    set_long("This huge steel mace is made from the steel " +
      "forged in Sanction. It has a slight red tint about it, and " +
      "if Sanction steel is anything to go by, you would assume this " +
      "mace is of good quality.\n");
    set_default_weapon(30,39,W_CLUB,W_BLUDGEON,W_BOTH);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 18000);
}
