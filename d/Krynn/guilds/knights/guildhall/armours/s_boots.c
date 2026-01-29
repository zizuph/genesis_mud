/* created by Aridor, 09/15/94 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */
inherit "/std/armour";
inherit "/d/Genesis/lib/commodity";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "../../local.h"

public void
create_armour()
{
    set_name("boots");
    add_name("armour");
    set_pname("boots");
    add_pname("armours");
    set_adj("steel");
    set_short("pair of steel boots");
    set_pshort("pairs of steel boots");
    set_long("These are the boots belonging to the set of Solamnic Armour. " +
         "They are made of steel and polished to shine brightly.\n");
    set_at(A_FEET);
    set_ac(25);


    set_commodity_name ("s_boots"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(25), 0);

    add_prop(VK_NOBUY, 1);
}

