
/* Knight weapons by Morrigan, Jan 10 97 */
/*
 * Added support for the commerce module in July 2002, by Boron
 * 
 * Altered by Navarre june 11th 2006.
 * Removed inscription from the long description, as it doesn't have one.

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
    set_name("lance");
    add_name(({"weapon","polearm"}));
    set_pname("lances");
    add_pname(({"polearms","weapons"}));
    set_adj("solamnic");
    add_adj("sleek");
    set_short("sleek solamnic lance");
    set_pshort("sleek solamnic lances");
    set_long("This is a magnificent lance, sleek and strong, truly "+
      "worthy the Solamnian Knights who favour it. Its length stretches "+
      "longer than a man, and the tip is tapered to a point with slender "+
      "barbs running along the edges of the shaft, a foot or so back from "+
      "the tip.\n");
    set_default_weapon(35, 40, W_POLEARM, W_IMPALE, W_BOTH);


    set_commodity_name ("s_halberd"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_WEAPON(25,35), 0);

    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,35));
    add_prop(VK_NOBUY, 1);
}

