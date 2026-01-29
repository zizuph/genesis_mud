inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
	{
	set_name(({"greaves","armour",}));
	set_pname(({"greaves","armours",}));
	set_short("shining crystal greaves");
	set_pshort("shining crystal greaves");
	set_long("A pair of shining crystal greaves, designed "+
		"to wear on the legs.\n");
	set_adj(({"shining", "crystal"}));
	set_default_armour(20, A_LEGS, ({3,1,-4}));
	}
