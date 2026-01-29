/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("pants");
    set_short("pair of pants");
    set_pshort("pairs of pants");
    set_long("This is a pair of pants made from linen. The linen is " +
	     "crude, but can still protect some.\n");
    set_ac(5);
    set_at(A_LEGS);
}
