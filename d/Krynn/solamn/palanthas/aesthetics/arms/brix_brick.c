/*
 * Common red brick pulled up from under the marble of the
 * streets of Palanthas and used as a cheap club and tool
 * of vandalism by the Brix gang.
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
	set_name("brick");
	set_adj(({"old", "red"}));
	set_short("old red brick");
	set_long("This worn, old, red brick looks suspiciously like the brick "
	+ "laid beneath the marble of the streets of Palanthas.  You could "
	+ "throw it through windows, smash things with it, or possibly use "
	+ "it as a crude clubbing object.\n");

	set_hit(7);
	set_pen(11);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);
}

