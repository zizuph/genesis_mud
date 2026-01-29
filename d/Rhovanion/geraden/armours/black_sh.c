
/* Basic armour file to be edited for use 
Geraden 941014
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
	set_name("shield");
	set_short("black banded shield");
	set_long(
		"A black shield worn by the clerics of the Great Emerald\n");
	set_adj("black");
	add_adj("banded");

	set_default_armour(20, A_SHIELD, 0, 0);
	set_am(({10, -5, -5}));
}
