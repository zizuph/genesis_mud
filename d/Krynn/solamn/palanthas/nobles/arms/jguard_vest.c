/*
 * Vest worn by jeweler's guard in nobles quarter.
 *
 * Mortis 10.2006
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include "../../local.h"

public void
create_armour()
{
	 set_name("vest");
	 set_pname("vests");
	 add_name(({"armour"}));
	 add_pname(({"armours"}));
	 set_adj("double-breasted");
	 add_adj("leather");
	 set_short("double-breasted leather vest");
	 set_pshort("double-breasted leather vests");
	 set_long("Thin, supple leather conceals the true protection of this "
	 + "vest, a series of form contoured iron plates.  Outwardly it "
	 + "appears as nothing more than a stylish fold over vest with buckled "
	 + "straps along its side and two rows of iron stud buttons up the "
	 + "front.  The image of a gem has been pressed into a small, iron "
	 + "disk below the folded, flared collar of the vest.\n");

	 set_ac(30);
	 set_at(A_TORSO);

	 add_prop(OBJ_I_VOLUME, 3500);
	 add_prop(OBJ_I_WEIGHT, 12000 +random(120));
	 add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45));
}
