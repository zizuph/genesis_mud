/* created by Aridor 04/97 */

inherit "/std/weapon";

#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

create_weapon()
{
    set_name("knife");
    set_adj("hunting");
    set_short("hunting knife");
    set_long("This knife is fairly large and looks like it could be " +
		"perfectly used for hunting.\n");

    set_hit(9);
    set_pen(6);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, 10 + F_VALUE_WEAPON(9,6));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(9,W_KNIFE));
    add_prop(OBJ_I_VOLUME, 600);

}
