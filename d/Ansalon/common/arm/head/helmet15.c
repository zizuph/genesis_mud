/* Navarre June 25th 2006, fixed unworn bug,
 * by adding set_short
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("coif");
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({ -5, 0, 5 }) );
    set_adj("chainmail");
    set_short("chainmail coif");
    set_long("This is a chainmail coif, head armourment " +
      "commonly worn by warriors.\n");
    add_prop(OBJ_I_VOLUME, 150);
}


