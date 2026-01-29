/*
 * Mortis 03.2006
 *
 * Improvised weapons used by merchant house Trusq
 * warehouse workers in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("knife");
	set_adj(({"box", "cutter", "box-cutter"}));
	set_short("box-cutter knife");
	set_long("With a blade as short as a razor and nearly as thin, the "
	+ "box-cutter knife is more of a utility tool for opening things than "
	+ "it is an effective weapon.\n");

	set_hit(9);
	set_pen(9);
	set_wt(W_KNIFE);
	set_dt(W_SLASH);
	set_hands(W_ANYH);
}

