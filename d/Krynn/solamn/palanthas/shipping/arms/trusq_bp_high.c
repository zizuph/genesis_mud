/* Mortis 03.2006
 *
 * Jent Port security force high guard cuirasse of
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
	set_name("cuirasse");
	set_adj("tight");
	add_adj(({"studded", "leather"}));
	set_short("tight studded leather cuirasse");
	set_long("Studded with darkened steel studs, this leather cuirasse has "
	+ "straps and ties up its sides so it may be worn snugly against the "
	+ "body.\n");

	set_ac(22 + random(6));
	set_am(({0, -1, 1}));
	set_at(A_BODY);

}
