/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("boots");
    set_short("pair of boots");
    set_pshort("pairs of boots");
    set_long("This is an ordinary pair of boots, with a tall shaft and " +
	     "made from leather. The leather is very smooth but " +
	     "thin.\n");
    set_ac(6);
    set_at(A_FEET);
}
