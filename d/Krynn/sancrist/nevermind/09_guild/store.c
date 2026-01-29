/*   Created by Dajala
 *   The storage room for the kit_gnome selling the parts of the types
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/sys/stdproperties.h"
#include "modules.h"

/*prototype*/
void reset_room();


void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);
	store_update(ob);
}

void
create_room()
{
	set_short("Store room");
	set_long("This is the store room for the workshop. The "
		+ "kits for the modules are kept here.\n");
	INSIDE;
	LIGHT;
	add_exit(GGUILD + "workshop", "out", 0);
	
	reset_room();
}

void
reset_room()
{
	object ob;
	int i;      
	seteuid(getuid(TO));

	for (i=0;i<sizeof(TYPES);i++)
	{
		if (!P("kit_for_" + TYPES[i], TO))
		{
			ob = clone_object(GGUILD + "obj/kit");
			ob->move(TO);
			ob->set_type(TYPES[i]);
		}
	}
}
