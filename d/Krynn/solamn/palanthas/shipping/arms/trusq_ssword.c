/* Mortis 03.2006
 *
 * Ssword used by merchant house Trusq high guard in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("shortsword");
	add_name(({"sword"}));
	set_adj("single-edged");
	add_adj("serrated");
	set_short("single-edged serrated shortsword");
	set_long("Two and a half feet long with a slight curve towards the tip, "
	+ "this single-edged short blade is serrated for a foot down its length "
	+ "from its curving steel hilt.  The handle has been wrapped tightly "
	+ "with padding and a layer of silk giving it a good grip, and its well "
	+ "balanced pommel is set with a large, clear crystal.\n");

	set_hit(31);
	set_pen(27);
	set_wt(W_SWORD);
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_ANYH);

	add_prop(OBJ_I_VALUE, 800 + random(475));
}
