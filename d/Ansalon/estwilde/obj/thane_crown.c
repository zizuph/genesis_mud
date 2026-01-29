/* Navarre July 3rd 2006 fixed double space in description */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("crown");
    set_ac(1);
    set_at(A_HEAD);
    set_adj("golden");
    set_short("golden crown");
    set_long("This beautiful piece of craftsmanship is " +
      "the crown of the Thane of the Hill Dwarves, the warleader "+
      "and King of those dwarves who wander the plains and " +
      "hills of Krynn. Crafted from pure gold and decorated with " +
      "jewels, this crown is one of the finest and most highly " +
      "prized artifacts of the dwarven nations.\n");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD));
    add_prop(OBJ_I_VALUE, 90000);
    add_prop(OBJ_M_NO_SELL,"Sell the Thane's crown? You don't want to do that!\n");
}


