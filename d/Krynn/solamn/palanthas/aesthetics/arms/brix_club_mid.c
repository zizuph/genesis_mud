/*
 * Two-by-four with nails used as a cheap club and tool
 * of intimidation by the Brix gang.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("board");
	set_adj(({"nail", "nails", "nailed"}));
	set_short("board with nails in it");
	set_pshort("boards with nails in them");
	set_long("A strip of crude hemp cloth wrapped around the end of this "
	+ "two by four plank of wood serves as its handle while a dozen nails "
	+ "put through the other end make it look like a spiked club when it is "
	+ "in fact little more than a board with nails in it.\n");

	set_hit(11);
	set_pen(20);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON | W_IMPALE);
	set_hands(W_ANYH);
}

