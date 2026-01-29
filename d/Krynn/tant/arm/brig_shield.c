/* The shield used by brigands
 * by Teth, Jan 18 1997
 */
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "../local.h"

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name("armour");
    add_pname("armours");
    set_adj("light");
    set_short("light shield");
    set_pshort("light shields");
    set_ac(9);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("This light shield offers some protection to one's " +
        "arms. Unfortunately, it is not much use for hits placed " +
        "on the body.\n");
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9));
}
