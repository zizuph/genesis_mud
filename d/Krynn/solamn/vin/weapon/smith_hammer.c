/* The hammer wielded by the Blacksmith in Vingaard Keep
 * modified by Teth, Dec 2, 1996
*/
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../local.h"

public void
create_weapon()
{
    set_name("hammer");
    add_name(({"weapon","club"}));
    set_pname("hammers");
    add_pname(({"weapons","clubs"}));
    set_adj("forging");
    set_short("forging hammer");
    set_pshort("forging hammers");
    set_long("This is a forging hammer. The peen of the hammer " +
        "is made of a strong alloy that has little malleability. " +
        "The handle of the hammer is smooth with use.\n");
    set_default_weapon(15, 20, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 1050);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15,25));
    add_prop(VK_NOBUY, 1);
}

