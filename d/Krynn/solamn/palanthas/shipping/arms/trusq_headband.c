/* Mortis 03.2006
 *
 * Jent Port security force guard headband of
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
	set_name("headband");
	add_name("band");
	set_adj("leather");
	add_adj(({"head"}));
	set_short("leather headband");
	set_long("Padded with an inner layer of cushioning, this band of sturdy "
	+ "leather fits around the head and forehead keeping sweat and hair out "
	+ "of the eyes while offering some small protection.\n");

	set_ac(10 + random(5));
	set_am(({0, -1, 1}));
	set_at(A_HEAD);

 	add_prop(OBJ_I_WEIGHT, 860 + random(80));
	add_prop(OBJ_I_VOLUME, 710 + random(70));
}
