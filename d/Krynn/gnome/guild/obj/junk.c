/* This is the object that all gnomish devices which collapse turn into.  */
/* Modified by Percy */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"


void
create_object()
{
	set_name("junk");
	add_name("k_junk");
	set_adj("gnomish");
	set_short("gnomish junk");
	set_long("This is a huge mess of junk metal and wood with no"
	 + " recognisable purpose or design. I guess only a gnome could"
	 + " make use of it!\n");

	add_prop(OBJ_I_WEIGHT, 2000);
	add_prop(OBJ_I_VOLUME, 1000);

	set_alarm(800.0, -1.0, "desint");
}

void
desint()
{
	if(living(E(TO)))
	{
		tell_room(E(E(TO)), QCTNAME(E(TO)) + " looses something.\n"
			, E(TO));
		E(TO)->catch_msg("The junk desintegrates into even smaller "
			+ "bits and pieces.\n");
	}
	else
		tell_room(E(TO), "The junk desintegrates into even smaller "
			+ "bits and pieces.\n");
	remove_object();
}
