/* 
 * Created by Mortis 09.2005
 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("apron");
    set_adj("clean");
	set_adj("green");
    set_short("clean green apron");
    set_long("This thin linen apron is crisp and clean.  It bears the white "
	+ "emblem of the Dawnbringer, a bust of a flowing haired woman her "
	+ "outstretched hand bearing a shining lantern.\n");
    set_ac(1);
set_at(A_WAIST);
}
