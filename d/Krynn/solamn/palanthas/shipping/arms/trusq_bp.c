/* Mortis 02.2006
 *
 * Jent Port security force guard breastplate of
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
	set_name("breastplate");
	set_adj("yellow-enameled");
	add_adj(({"yellow", "steel"}));
	set_short("yellow-enameled steel breastplate");
	set_long("This ornamentally trimmed breastplate has been enameled "
	+ "yellow on its left half while its right remains plain polished "
	+ "steel.\n");

	set_ac(32 + random(6));
	set_am(({0, 1, -1}));
	set_at(A_BODY);
}
