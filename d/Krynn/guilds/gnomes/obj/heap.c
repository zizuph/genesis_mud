/* Created by Dajala
 * Is cloned when a member 'checked' a magical item
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../guild.h"


void
create_object()
{
	set_name("heap");
	add_name("heap of parts");
	add_name("parts");
   set_adj("gnomish");
	set_short("heap of parts");
	set_long("This is a small heap of items of different shapes "
		+ "and sizes. It seems as if it once had been a whole but "
		+ "it is impossible to determine its origin.\n");
	add_prop(OBJ_I_WEIGHT, 1000);
	add_prop(OBJ_I_VOLUME, 500);
	set_alarm(800.0, -1.0, "desint");
}

void
desint()
{
	if(living(E(TO)))
	{
		tell_room(E(E(TO)), QCTNAME(E(TO)) + " looses something.\n"
			, E(TO));
		E(TO)->catch_msg("The heap disintegrates into even smaller "
			+ "bits and pieces.\n");
	}
	else
		tell_room(E(TO), "The heap disintegrates into even smaller "
			+ "bits and pieces.\n");
	TO->remove_object();
}
