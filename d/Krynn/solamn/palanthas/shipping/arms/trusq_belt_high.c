/* Mortis 03.2006
 *
 * Jent Port security force high guard belt of
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
	set_name("belt");
	set_adj("braided");
	add_adj(({"leather"}));
	set_short("braided leather belt");
	set_long("Five thick strands of firm leather have been braided together "
	+ "into a star Enta pattern in this well made belt.  Its small buckle "
	+ "is made of darkened steel with a band of black velvet around the "
	+ "buckle's lock pin.\n");

	set_ac(6 + random(3));
	set_am(({0, -1, 1}));
	set_at(A_WAIST);

}
