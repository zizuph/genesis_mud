/*
	*Sharpened pole for banner making
	*Altrus, May 2005
*/

inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

void create_object()
{
	set_name("standard");
	set_pname("standards");
	add_name("_unfinished_standard");
	set_adj("unfinished");
	set_adj("battle");
	
	add_prop(OBJ_I_WEIGHT, 1750); 	
	add_prop(OBJ_I_VOLUME, 550);
}


