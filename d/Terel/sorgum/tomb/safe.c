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
	 set_long("It's a large steel trunk.  It looks much too strong to " +
		  "_break_ into.\n");
	 set_adj(({"large", "steel"}));
	 
	 add_prop(CONT_I_WEIGHT, 100000);
	 add_prop(CONT_I_MAX_WEIGHT, 120000);
	 add_prop(CONT_I_VOLUME, 20000);
	 add_prop(CONT_I_MAX_VOLUME, 40000);
	 add_prop(CONT_I_TRANSP, 0);
	 add_prop(CONT_I_RIGID, 1);
	 seteuid(getuid(TO));
	 /* MONEY_MAKE_PC(100 + random(10))->move(TO); 
	  Since this safe can't be gotten into, I removed the money
	  to reduce memory. Trofast 9-98*/
	 add_prop(CONT_I_LOCK, 1);
	 add_prop(CONT_I_CLOSED, 1);
	 add_prop(OBJ_I_NO_GET, 1);
	 add_prop("_melted", 0);


}
