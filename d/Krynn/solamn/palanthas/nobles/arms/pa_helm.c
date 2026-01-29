/*
 * Standard, mid quality helmet of Palanthian
 * Armour guard service (head protection).
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
	 set_name("helmet");
	 set_pname("helmets");
	 add_name(({"armour"}));
	 add_pname(({"armours"}));
	 set_adj("open-faced");
	 add_adj("sallet");
	 set_short("open-faced sallet helmet");
	 set_pshort("open-faced sallet helmets");
	 set_long("This one pieced, low-domed helmet flares out as it reaches "
	 + "the neck providing there some protection.  Though open-faced for "
	 + "a clear field of view, it still protects the face from lateral "
	 + "blows.  It is secured in place with a buckled chin and neck "
	 + "harness.\n");

  
	 set_ac(27);
	 set_at(A_HEAD);

	 add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(45));
}
