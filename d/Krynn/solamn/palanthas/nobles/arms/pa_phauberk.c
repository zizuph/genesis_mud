/*
 * Standard, mid quality platemail hauberk of Palanthian
 * Armour guard service.
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
	 set_name("hauberk");
	 set_pname("hauberks");
	 add_name(({"armour"}));
	 add_pname(({"armours"}));
	 set_adj("snug");
	 add_adj("platemail");
	 set_short("snug platemail hauberk");
	 set_pshort("snug platemail hauberks");
	 set_long("Thin, form-fitting plates of steel overlap atop a soft "
	 + "inner layer of leather to form this low-profile platemail "
	 + "hauberk.  Covering the arms and body, it protects its inner "
	 + "joints with fine brigandine and, unlike bulkier platemails, allows "
	 + "for a smoother range of motion even in enclosed spaces like "
	 + "indoors.\n");

	 set_ac(37);
	 set_at(A_TORSO | A_ARMS);

	 add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45));
}
