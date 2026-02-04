inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Terel/common/terel_std_rec.h"
#include "tomb.h"

init()
{
     ::init();
}

create_container()
{
         set_name("trunk");
	 set_short("steel trunk");
	 set_long("It's a large steel trunk.  Something has melted a hole " +
		  "in the surface\n");
	 set_adj(({"large", "steel"}));
	 
	 add_prop(CONT_I_WEIGHT, 100000);
	 add_prop(CONT_I_MAX_WEIGHT, 120000);
	 add_prop(CONT_I_VOLUME, 20000);
	 add_prop(CONT_I_MAX_VOLUME, 40000);
	 add_prop(CONT_I_TRANSP, 1);
	 add_prop(CONT_I_RIGID, 1);
	 add_prop(CONT_I_LOCK, 0);

	 seteuid(getuid(TO));
	 MONEY_MAKE_PC(10 + random(10))->move(TO);
	 
	 add_prop(CONT_I_CLOSED, 0);
	 add_prop("_melted", 1);	 
}
