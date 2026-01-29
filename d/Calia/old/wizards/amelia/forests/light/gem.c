/*
*  adapted by Amelia, for use in the Light Forest
*/

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_object()
{
	set_name("gem");
	set_adj(({"small", "green"}));
	set_adj("green");
	set_short("small green gem");
	set_pshort("small green gems");
	set_long("As you brush the dirt off, you see this is a "+
		"small gem!  Better keep it, it might be worth something.\n");
	add_prop(OBJ_I_VALUE, 300);
	add_prop(OBJ_I_WEIGHT, 25);
	add_prop(OBJ_I_VOLUME, 20);
}

string
query_recover()
{
    return MASTER;
}
