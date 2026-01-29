/* The grease from Xak Tsaroth. One of the spell components
	for the sabre quest. */
/* Created by Macker April 12th, 1995 */

inherit "/std/object.c";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

create_object()
{
	set_name("glob of grease");
	add_name("glob");
	add_name("grease");
	add_name("sabre_quest_ob2");
	add_name("sabre_quest_item");
	add_adj("big");
	set_long("This is a big glob of grease. It smells like it " +
		"might have come from the hair of a gully dwarf. " +
		"It doesn't look particularly usefull or valuable. " +
		"In fact, it really stinks.\n");
	add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VALUE, 1);
}


