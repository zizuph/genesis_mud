/*
	*Sharpened pole for banner making
	*Altrus, May 2005
*/

inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

void create_object()
{
	set_name("pole");
	set_pname("poles");
	add_name("_a_sharp_pole");
	set_adj("long");
	set_adj("pointed");
	set_short("long pointed pole");
	set_pshort("long pointed poles");
	set_long("This is a long pole with a sharpened tip.\n");
	
	add_prop(OBJ_I_WEIGHT, 1500); 	
	add_prop(OBJ_I_VOLUME, 500);
}


