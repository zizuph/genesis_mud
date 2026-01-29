inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
	{
	set_name(({"helm","helmet","armour",}));
	set_pname(({"helms","helmets","armours",}));
	set_short("spiked crystal helmet");
	set_pshort("spiked crystal helmets");
	set_long("A high helmet made of crystal with a large "+
		"crystal spike  on the top.\n");
	set_adj(({"high", "crystal"}));
	set_default_armour(20, A_HEAD | A_NECK, ({3,1,-4}));
	}
