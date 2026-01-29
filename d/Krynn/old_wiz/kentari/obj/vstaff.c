inherit "/std/weapon.c";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
	set_name(({ "staff", "polearm" }));
	set_pname(({ "staffs", "polearms", }));
	set_adj(({ "polished", "valenwood"}));
	set_short("polished valenwood staff");
	set_pshort("polished valenwood staffs");
	set_long("This stout polearm is made of valenwood, a " +
		"Krynnish hardwood of extreme durability. Polished " +
		"and obviously well cared for, this staff is quite " +
		"heavy compared to what you'd expect, but then, it " +
		"would take quite a beating to break too. The quality " +
		"of this staff makes it easy to see why valenwood is " +
		"such a commodity in Krynn, and why it is so effective " +
		"for making polearms.\n");

	set_default_weapon(33, 22, W_POLEARM, W_BLUDGEON, W_BOTH);
	update_prop_settings();
	set_wf(TO);
	add_prop(OBJ_I_VOLUME, 7500);
	add_prop(OBJ_I_WEIGHT, 7500);
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(33,22) + 200);
}


