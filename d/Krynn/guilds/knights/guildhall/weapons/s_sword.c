/* The Knight guard sword in Vingaard Keep.
 * modified by Teth, Dec 2, 1996
*/
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
    set_name("blade");
    add_name(({"weapon","sword"}));
    set_pname("blades");
    add_pname(({"swords","weapons"}));
    set_adj("solamnic");
    add_adj("steel");
    set_short("solamnic blade");
    set_pshort("solamnic blades");
    set_long("This finely-honed blade is made of Solamnic steel. " +
        "The sword has a small inscription placed near the crafted " +
        "hilt.\n");
    AI(({"inscription","small inscription"}),"The inscription " +
        "reads: Standard Issue of the Vingaard Keep armoury.\n");
    set_default_weapon(29, 25, W_SWORD, W_SLASH || W_IMPALE, W_ANYH);


    set_commodity_name ("s_sword"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_WEAPON(29,25), 0);

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 2200);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,25));
    add_prop(VK_NOBUY, 1);
}

