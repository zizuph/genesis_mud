
/* Basic armour file to be edited for use 
Geraden 941014
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
	set_name("bracers");
	set_short("black banded bracers");
	set_long(
		"Black banded bracers worn from the clerics of the Great "+
		"Emerald\n");
	set_adj("black");
	add_adj("banded");
	
	set_default_armour(20, A_ARMS, 0, 0);
	set_am(({5, -2, -3}));
}
