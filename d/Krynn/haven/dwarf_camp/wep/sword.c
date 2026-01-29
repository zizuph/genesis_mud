
inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/haven/local.h"

public void
create_weapon()
{
    set_name("sword");
    add_name(({"weapon","shortsword"}));
    set_pname("swords");
    add_pname(({"shortswords","weapons"}));
    set_adj(({"short", "broad-bladed"}));
    add_adj("steel");
    set_short("short broad-bladed sword");
    set_pshort("short broad-bladed swords");
    set_long("This is a short sword, not much longer than a "+
      "typical dagger, but the blade is unusually broad. It "+
      "appears to be dwarven, and of fine quality.\n");

    set_default_weapon(27, 25, W_SWORD, W_SLASH || W_IMPALE, W_ANYH);

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(27,25));
}
