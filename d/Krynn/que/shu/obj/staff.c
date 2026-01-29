/* created by Aridor 04/97 */

inherit "/std/weapon";

#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

create_weapon()
{
    set_name("staff");
    set_pname("staves");
    set_adj("wooden");
    add_adj("long");
    set_short("long wooden staff");
    set_pshort("wooden staves");
    set_long("This long wooden staff is very smooth and looks perfect to hit " +
      "someone from a range.\n");

    set_hit(32);
    set_pen(10);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32,10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(32,W_POLEARM));
    add_prop(OBJ_I_VOLUME, 4000);

}
