/* Created by Dajala
 * Is cloned into the inventory when the player uses the GestureMatic
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>


void
create_object()
{
	set_name("_g_stopper_");
	set_short("stopper");
	set_long("This invisible object is cloned to keep the player from "
		+ "walking around while the GestureMatic(tm) is operat"
		+ "ional.\n");
	add_prop(OBJ_I_WEIGHT, 0);
	add_prop(OBJ_I_VOLUME, 0);
	add_prop(OBJ_M_NO_DROP, 1);
	set_no_show();
}

void
init()
{
	add_action("check_all_commands", "", 1);
}

int
check_all_commands(string str)
{
	string verb;

	verb = query_verb();
	if(verb == "west" || verb == "northwest" || verb == "north"
		|| verb == "northeast" || verb == "east" 
		|| verb == "southeast" || verb == "south"
		|| verb == "southwest" || verb == "sneak"
		|| verb == "go" || verb == "enter"
		|| verb == "back" || verb == "common" 
		|| verb == "up" || verb == "down"
	  )
	{
		write("You cannot move with a bulky thing like the "
			+ "GestureMatic hanging from your gizmo. "
			+ "You'll need to fold it first.\n");
		return 1;
	}
	return 0;
}

