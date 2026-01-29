/* Wandering Cleric of Morgion's Boots.
 * by Teth, Feb 21 1997
 */

inherit "/std/armour";
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_armour()
{
    set_name("boots");
    set_pname("boots");
    add_name("armour");
    add_pname("armours");
    set_adj(({"soft","leather"}));
    add_name("pair of boots");
    add_pname("pairs of boots");
    set_short("pair of soft leather boots");
    set_pshort("pairs of soft leather boots");
    set_ac(8);
    set_at(A_FEET);
    set_long("This is a fine pair of leather boots, softened with use and " +
       "time.\n");
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(8, A_LEGS));
    /*should be A_FEET but that results in 0!*/
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
}
