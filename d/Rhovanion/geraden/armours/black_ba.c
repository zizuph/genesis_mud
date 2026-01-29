
/* Basic armour file to be edited for use 
Geraden 941014
*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_armour()
{
	set_name("mail");
	set_short("black banded mail");
	set_long(
		"A suit of black banded mail worn by the clerics of the "+
		"Great Emerald.\n");
	set_adj("black");
	add_adj("banded");

	set_ac(40);
	set_am(({10, -5, -5}));
	set_at(A_BODY);
}
