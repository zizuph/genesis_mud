/* created by Aridor, 09/15/94 */

inherit "/std/armour";

#include <wa_types.h>
#include <ss_types.h>

void
create_armour()
{
    set_name("boots");
    set_adj("steel");
    set_short("pair of steel boots");
    set_pshort("pairs of steel boots");
    set_long("These are the boots belonging to the set of Solamnic Armour. " +
	     "They are made of steel and polished to shine brightly.\n");
    set_at(A_FEET);
    set_ac(25);
}

