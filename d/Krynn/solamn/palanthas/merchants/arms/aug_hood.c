/* 
 * Mortis 04.2006
 *
 * Hood worn by bowyer Aug in Palanthas
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../../local.h"

public void
create_armour()
{
	set_name("hood");
	set_adj("enshrouding");
	add_adj(({"grey"}));
	set_short("enshrouding grey hood");
	set_long("Sewn of grey dupion, this hood hangs over the forehead and "
	+ "wraps around the lower face enshrouding its wearers face in shadow.  "
	+ "It is long enough to rest on the shoulders and is lined with thin "
	+ "leather platelets offering minor protection as well.\n");

	set_ac(12 + random(3));
	set_am(({-1, 0, 1}));
	set_at(A_HEAD);

	add_prop(OBJ_I_VOLUME, 600 + random(300));
	add_prop(OBJ_I_WEIGHT, 400 + random(150));
	add_prop(OBJ_I_VALUE, 175 + random(50));
}
