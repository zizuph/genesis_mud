/* Mortis 02.2006
 *
 * Light chainmail shirt worn by city guards in Palanthas.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../local.h"

#define VK_NOBUY                    "_vkeep_shop_no_buy"

void setup_gear();

public void
create_armour()
{
	set_name("shirt");
	set_adj("light");
	add_adj("chainmail");
	set_short("light chainmail shirt");
	set_long("Very fine and small steel rings have been used in the "
	+ "construction of this shirt keeping it light.  The neck is not "
	+ "large enough to fit over your head.  Instead, there is a seam "
	+ "running along the left up the side, under the arm, and across "
	+ "the shoulder to the neck for you to slip into.  Small leather "
	+ "straps, over the shoulder and up the side, buckle the shirt "
	+ "closed, keeping it snugly in place.\n");

	set_alarm(0.5, 0.0, "setup_gear");
}

void
setup_gear()
{
	set_ac(32 + random(3));
	set_am(({0, 2, -2}));
	set_at(A_BODY);

	add_prop(OBJ_I_VOLUME, 2750 + random(350));
	add_prop(OBJ_I_WEIGHT, 3000 + random(400));
	add_prop(OBJ_I_VALUE, 750 + random(200));
	add_prop(VK_NOBUY, 1);
}
