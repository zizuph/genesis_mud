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
    set_name("mace");
    add_name(({"weapon","club"}));
    set_pname("mace");
    add_pname(({"maces","weapons"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_adj(({"heavy", "solamnic"}));
    set_short("heavy solamnic mace");
    set_pshort("heavy solamnic maces");
    set_long("A short, but heavy, mace. This mace is similar in fashion to "+
        "the type dwarves use, weighted at the end to lend more power to "+
        "the swing. The head of the mace is ball-shaped, and somewhat thicker "+
        "than the rest. A small inscription is carved along the hilt of the "+
        "mace.\n");
    set_default_weapon(23,25, W_CLUB, W_BLUDGEON, W_ANYH);

    set_commodity_name ("s_mace"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_WEAPON(23,25), 0);

    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(23,25));
    add_prop(VK_NOBUY, 1);
}

