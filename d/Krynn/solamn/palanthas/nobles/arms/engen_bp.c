/* by Mortis 10.2005
 *
 * Includes support for the commerce module.
 * Sir Engen's breastplate.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";
inherit "/d/Genesis/lib/commodity";

#include <wa_types.h>
#include <formulas.h>
#include "../../local.h"

#define VK_NOBUY                    "_vkeep_shop_no_buy"

public void
create_armour()
{
	 set_name("breastplate");
	 set_pname("breastplates");
	 add_name(({"armour"}));
	 add_pname(({"armours"}));
	 set_adj("copper-emblazoned");
	 add_adj("emblazoned");
	 set_short("copper-emblazoned breastplate");
	 set_pshort("copper-emblazoned breastplates");
	 set_long("This polished breastplate is either new or virtually "
	 + "unused.  Upon the breast emblazoned in copper leaf is the "
	 + "Solamnic symbol of a crown around a downward pointing "
	 + "greatsword.  The right shoulder piece bears a great pauldron "
	 + "with neckshield and overlapping bands of steel plate reaching "
	 + "to the elbow where a chainmail sleeve continues to the wrist.  "
	 + "The left shoulder bears a lighter pauldron from which a "
	 + "chainmail sleeve extends to the wrist.  A steel peg extends "
	 + "outward from the bottom of the left side of the breastplate, "
	 + "an unusual addition to this sort of armour.\n");
	 add_item(({"symbol", "copper symbol", "solamnic symbol"}),
	   "The symbol has been carefully emblazoned upon the breastplate "
	 + "in smooth, flawlessly applied copper leaf.  The crown is "
	 + "typical of the stylizations used in Solamnic symbology.  The "
	 + "greatsword is nicely detailed and about nine inches long.  It "
	 + "is positioned above the left breast of the breastplate.\n");
	 set_ac(40);
	 set_at(A_TORSO | A_ARMS);

	 set_commodity_name ("s_armour");
	 set_commodity_value(F_VALUE_ARMOUR(45), 0);

	 add_prop(OBJ_I_VOLUME, 3500);
	 add_prop(OBJ_I_WEIGHT, 12000 +random(120));
	 add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45));
	 add_prop(VK_NOBUY, 1);
}
