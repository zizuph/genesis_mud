/* Mortis 02.2006
 *
 * Jent Port security force guard greaves of
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
	set_name("greaves");
	set_adj("bolted");
	add_adj(({"steel"}));
	set_short("pair of bolted steel greaves");
	set_pshort("pairs of bolted steel greaves");
	set_long("This pair of greaves is trimmed in small steel bolts holding "
	+ "its outer plates snugly against its padded leather inner surface "
	+ "to create a cheap but sturdy armour.\n");

	set_ac(28 + random(6));
	set_am(({0, 1, -1}));
	set_at(A_LEGS);
}
