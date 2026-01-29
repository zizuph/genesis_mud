/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("leggings");
    set_short("pair of leggings");
    set_pshort("pairs of leggings");
    set_long("This is a pair of leggings made from cotton. It is of " +
	     "a greyish color and looks very plain.\n");
    set_ac(3);
    set_at(A_LEGS);
}
