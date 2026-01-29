/* 
 * Mortis 04.2006
 *
 * Vest worn by bowyer Aug in Palanthas
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
	set_name("vest");
	set_adj("sable");
	add_adj(({"armoured"}));
	set_short("armoured sable vest");
	set_long("Thick plates of hardened leather studded to a vest of supple "
	+ "leather are covered by a soft sable fur with a rich sheen and deep "
	+ "black shades.\n");

	set_ac(35 + random(2));
	set_am(({-3, 1, 2}));
	set_at(A_BODY);

	add_prop(OBJ_I_VOLUME, 9400 + random(1350));
	add_prop(OBJ_I_WEIGHT, 9600 + random(1800));
	add_prop(OBJ_I_VALUE, 675 + random(250));
}
