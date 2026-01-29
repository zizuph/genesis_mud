/* Mortis 02.2006
 *
 * Common weapons used by merchant house Trusq guards in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("sword-axe");
	add_name(({"sword", "axe", "swordaxe"}));
	set_adj("wavy-edged");
	add_adj("steel");
	set_short("wavy-edged steel sword-axe");
	set_long("The sword-axe has a long, leather wrapped handle and a small "
	+ "ring hilt from which extends a thin, three foot axe blade more akin "
	+ "to a sword blade but wielded in combat with an axe's style.  The "
	+ "blade has three large, curvy waves sharpened into its edge.  Though "
	+ "seemingly unwieldly, it is capable of damaging chops and slices.\n");

	set_hit(30);
	set_pen(35);
	set_wt(W_AXE);
	set_dt(W_SLASH);
	set_hands(W_ANYH);
}

