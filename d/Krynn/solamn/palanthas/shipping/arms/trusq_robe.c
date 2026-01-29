/* Mortis 02.2006
 *
 * Jent Port security force guard robe bearing symbol of
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
	set_name("robe");
	set_adj("leather-sleeved");
	add_adj(({"yellow", "blue"}));
	set_short("leather-sleeved yellow and blue robe");
	set_long("The uniform robe of Jent Port Security Force guards bearing "
	+ "the symbol of merchant house Trusq, a pair of gold balls each hanging "
	+ "from chains on opposite sides of a pronged balance above its left "
	+ "breast and much larger on its back.  The left half of the robe is "
	+ "yellow while the right half is light blue.  Banded leather sleeves "
	+ "run from the padded shoulders to the forearms.\n");

	set_ac(7);
	set_am(({-1, 0, 1}));
	set_at(A_ROBE | A_ARMS);
}
