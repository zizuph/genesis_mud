/* Mortis 02.2006
 *
 * Jent Port security force guard hood of
 * merchant house Trusq high guard.
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
	set_name("helm");
	set_adj("bolted");
	add_adj(({"steel", "dome"}));
	set_short("bolted steel dome helm");
	set_long("This helm has a dome bulging out over the forehead, a steel "
	+ "ridge, and bolts along its edges holding its leather padding snugly "
	+ "inside.  It's a cheap armour but sturdy.\n");

	set_ac(22 + random(6));
	set_am(({0, 1, -1}));
	set_at(A_HEAD);
}
