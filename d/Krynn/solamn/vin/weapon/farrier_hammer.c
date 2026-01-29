/* The hammer wielded by the Farrier in Vingaard Keep.
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
    set_adj("shoeing");
    set_short("shoeing hammer");
    set_pshort("shoeing hammers");
    set_long("This is a shoeing hammer, used by farriers to " +
        "tack horseshoes onto the hooves of horses. It has an " +
        "oak handle.\n");
    set_default_weapon(15, 20, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 1050);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15,25));
    add_prop(VK_NOBUY, 1);
}

