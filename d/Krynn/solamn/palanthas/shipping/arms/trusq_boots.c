/* Mortis 02.2006
 *
 * Jent Port security force guard boots of
 * merchant house Trusq.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../../local.h"

void
create_armour()
{
	set_name("boots");
	set_adj("leather");
	add_adj(({"yellow", "blue"}));
	set_short("pair of yellow and blue leather boots");
	set_pshort("pairs of yellow and blue leather boots");
	set_long("These inexpensive but sturdy boots are dyed yellow on the left "
	+ "and light blue on the right.\n");

	set_ac(8);
	set_am(({1, -1, 0}));
	set_at(A_FEET);
}
