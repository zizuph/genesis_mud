/* created by Aridor, 09/06/94 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("shoes");
    set_short("pair of shoes");
    set_pshort("pairs of shoes");
    set_long("This is an ordinary pair of shoes, they are used already, " +
	     "but you are certain they will be of good service to you if you " +
	     "intend to travel.\n");
    set_ac(3);
    set_at(A_FEET);
}
