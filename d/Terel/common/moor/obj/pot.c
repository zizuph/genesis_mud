inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

init()
{
     ::init();
}

create_container()
{
         set_name("pot");
	 set_short("iron pot");
	 set_pshort("iron pots");
	 set_long("It's a polished iron pot.\n");
	 set_adj(({"large", "polished"}));
	 
	 add_prop(OBJ_I_VALUE, 200 + random(20));

	 add_prop(CONT_I_WEIGHT, 100000);
	 add_prop(CONT_I_MAX_WEIGHT, 120000);
	 add_prop(CONT_I_VOLUME, 20000);
	 add_prop(CONT_I_MAX_VOLUME, 40000);
	 add_prop(CONT_I_TRANSP, 1);
	 add_prop(CONT_I_RIGID, 1);
}
