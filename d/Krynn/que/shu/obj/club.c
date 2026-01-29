/* created by Aridor 04/97 */

inherit "/std/weapon";

#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

create_weapon()
{
    set_name("club");
    set_adj("wooden");
    add_adj("nailed");
    set_short("nailed wooden club");
    set_long("This nailed wooden club is fairly large and looks perfect to smash " +
		"something.\n");

    set_hit(7);
    set_pen(10);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(7,10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(7,W_CLUB));
    add_prop(OBJ_I_VOLUME, 1600);

}
