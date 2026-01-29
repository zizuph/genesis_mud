/* The gnomish nametag from the gnome area of Krynn. One of the spell
	components for the sabre quest. */
/* Created by Macker April 12th, 1995 */

inherit "/std/object.c";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

create_object()
{
	set_name("tag");
	add_name("nametag");
	add_adj("gnomish");
	add_name("sabre_quest_ob3");
	add_name("sabre_quest_item");
	add_adj("name");
	set_long("This is a gnomish nametag. It is quite long, even " +
		"though the name on it is abreiviated. The full name " +
		"would have used way too much material.\n");
	add_prop(OBJ_I_VOLUME, 150);
	add_prop(OBJ_I_WEIGHT, 70);
	add_prop(OBJ_I_VALUE, 50);
	add_item("name", "Bozdilcrankinthwakidorious...\n");
	add_cmd_item("name", "read", "Bozdilcrankinthwakidorious...\n");

}

