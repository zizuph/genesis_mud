/* created by Aridor, 09/15/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("guards");
    set_adj("steel");
    set_short("pair of steel guards");
    set_pshort("pairs of steel guards");
    add_adj("leg");
    set_long("These leg guards belong to the set of Solamnic Armour. " +
	     "They are made of steel and polished to shine brightly.\n");
    set_ac(30);
    set_at(A_LEGS);
}
