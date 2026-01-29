/* Mortis 03.2006
 *
 * Robe of the lord of merchant house Trusq.
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
	set_name("robe");
	set_adj("gold-emblemed");
	add_adj(({"yellow", "blue"}));
	set_short("gold-emblemed yellow and blue robe");
	set_long("This exquisitely tailored robe bears a large, gold disc of "
	+ "the symbol of merchant house Trusq, a pair of gold balls each hanging "
	+ "from chains on opposite sides of a pronged balance pinned above its "
	+ "left breast and much larger on its back.  The left half of the robe is "
	+ "light blue while the right half is yellow.  The inside is padded with "
	+ "swansdown and is amazingly soft and comfortable.\n");

	set_ac(10);
	set_am(({-1, 0, 1}));
	set_at(A_ROBE);

	add_prop(OBJ_I_VALUE, 900 + random(275));
}
