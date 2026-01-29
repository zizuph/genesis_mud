
/* Basic armour file to be edited for use 
Geraden 941014
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
	set_name("boots", "pair of boots");
	set_pname ("pairs of boots");
	set_short("pair of black banded boots");
	set_pshort("pairs of black banded boots");
	set_long(
		"A pair of black banded boots worn by the clerics of the "+
		"Great Emerald.\n");
	set_adj("black");
	add_adj("banded");

	set_default_armour(10, A_FEET, 0, 0);
}
