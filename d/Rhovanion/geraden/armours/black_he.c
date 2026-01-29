
/* Basic armour file to be edited for use 
Geraden 941014
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
	set_name("helmet");
	set_short("black banded helmet");
	set_long(
		"A black banded helmet worn by the clerics of the Great "+
		"Emerald.\n");
	set_adj("black");
	add_adj("banded");

	set_default_armour(30, A_HEAD,0,0);
	set_am(({6, -3, -3}));
}
