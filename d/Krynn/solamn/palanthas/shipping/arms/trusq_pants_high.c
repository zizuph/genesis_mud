/* Mortis 03.2006
 *
 * Jent Port security force high guard pants of
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
	set_name("pants");
	set_adj("tight");
	add_adj(({"leather"}));
	set_short("pair of tight leather pants");
	set_pshort("pairs of tight leather pants");
	set_long("This pair of soft leather pants is meant to be worn snugly.  "
	+ "It has a drawstring built into the waist, and strings up the outside "
	+ "of the legs for tightening it down from the thighs to the calves.\n");

	set_ac(21 + random(4));
	set_am(({-1, 0, 1}));
	set_at(A_LEGS);
}
