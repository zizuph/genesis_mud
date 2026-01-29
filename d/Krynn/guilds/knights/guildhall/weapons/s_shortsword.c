/* Knight weapons by Morrigan, Jan 10 97 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */
inherit "/std/weapon";
inherit "/d/Genesis/lib/commodity";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../../local.h"

public void
create_weapon()
{
    set_name("shortsword");
    add_name(({"weapon","sword"}));
    set_pname("shortswords");
    add_pname(({"swords","weapons"}));
    set_adj("solamnic");
    add_adj("steel");
    set_short("solamnic shortsword");
    set_pshort("solamnic shortswords");
    set_long("A finely crafted sword, about one and a half times the length "+
        "of a dagger. Because of it's small size and light weight, it "+
        "can be used quickly, and in small areas, making it a deadly "+
        "weapon. A small inscription is carved along the lower part "+
        "of the blade.\n");
    AI(({"inscription", "small inscription"}), "The inscription reads: "+
        "Standard Issue of the Vingaard Keep Armoury.\n");
    set_default_weapon(27, 22, W_SWORD, W_SLASH || W_IMPALE, W_ANYH);

    set_commodity_name ("s_shortsword"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_WEAPON(27,22), 0);

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 2200);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(27,22));
    add_prop(VK_NOBUY, 1);
}

