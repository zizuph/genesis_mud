/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("sandals");
    set_short("pair of sandals");
    set_pshort("pairs of sandals");
    set_long("This is an ordinary pair of sandals, they're quite used " +
	     "already, but very solid leather material and you are " +
	     "certain they will be of good service to you if you intend " +
	     "to travel.\n");
    set_ac(1);
    set_at(A_FEET);
}
