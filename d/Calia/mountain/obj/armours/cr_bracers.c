inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
	

void
create_armour()
	{
	set_name(({"bracers","armour",}));
	set_pname(({"bracers","armours",}));
	set_short("shining crystal bracers");
	set_pshort("shining crystal bracers");
	set_long("Some bracers made of crystal, hard as diamond.  "+
		"They are made for wearing on the arms.\n");
	set_adj(({"shining", "crystal"}));
	set_default_armour(20, A_ARMS, ({3,1,-4}));
	}
