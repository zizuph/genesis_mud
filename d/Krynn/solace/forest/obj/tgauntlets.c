inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("gauntlets");
    set_short("pair of chain-link gauntlets");
    set_pshort("pairs of chain-link gauntlets");
    set_long("This is a pair of chain-link gauntlets, flexible and " +
             "somewhat comfortable. However, they reek of hobgoblin " +
             "sweat.\n");
    set_adj("chain-link");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_ac(10);
    set_am(({ 2, 2, -2 }));
    set_at(A_HANDS);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_HANDS));
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}

