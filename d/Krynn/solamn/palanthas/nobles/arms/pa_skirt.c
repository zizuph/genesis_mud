/*
 * Standard, mid quality brigandine skirt of Palanthian
 * Armour guard service (upper leg protection).
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
	 set_name("skirt");
	 set_pname("skirts");
	 add_name(({"armour"}));
	 add_pname(({"armours"}));
	 set_adj("brigandine");
	 set_short("brigandine skirt");
	 set_pshort("brigandine skirts");
	 set_long("Though not a typical skirt, the resemblance is similar.  Two "
	 + "halves of brigandine, thick canvas with long, thin steel plates "
	 + "woven through it, hang almost to the knees covering all but the "
	 + "inside of the thighs.  Numerous iron loops top this armour for a "
	 + "belt to fit through allowing it to be worn hanging from the waist, "
	 + "and straps at the bottom buckle above the insides of the knees to "
	 + "keep them in place.  Brigandine is not as heavy as plate, but "
	 + "neither is it as protective.\n");

  
	 set_ac(17);
	 set_at(A_LEGS);

	 add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45));
}
