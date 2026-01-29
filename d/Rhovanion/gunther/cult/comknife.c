inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

create_weapon()
{
	set_short("ritual knife");
	set_long("This knife is intended for use in ritual sacrifice"
		+" but seems to function well as a weapon, too. The blade"
		+" is made of smoke-black steel engraved with the texts of"
		+" the rite and the handle carved from some kind of bone."
		+" Two polished red stones sit in the eyes in the skull carved"
		+" at the top of the handle.\n");
		
	set_name("knife");
	set_adj("ritual");
	
	add_name("_cult_knife");
	
	set_dt(W_SLASH);
	set_wt(W_KNIFE);
	
	set_pen(30);	/* make it easy to cut out hearts with :) */
	set_hit(15);
}

		
	