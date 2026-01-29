/* Mortis 02.2006
 *
 * Apron of cook from kitchen of merchant house Trusq.
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
	set_name("apron");
	set_adj("white");
	add_adj(({"linen"}));
	set_short("white linen apron");
	set_long("A clean, white linen apron worn by chefs and cooks while at "
	+ "work in a kitchen, it has the symbol of merchant house Trusq, a pair "
	+ "of gold balls each hanging from chains on opposite sides of a pronged "
	+ "balance sewn over the left shoulder.\n");

	set_ac(2);
	set_am(({-1, 0, 1}));
	set_at(A_ROBE);
}
