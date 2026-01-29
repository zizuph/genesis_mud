/*
	*Quest item, for mushroom quest for Mrs. Maggot
	*Altrus, March 2005
*/

#include <stdproperties.h>

inherit "/std/object";

void create_object()
{
	set_name("mushrooms");
	add_name("handful");
	add_name("_maggot_mushrooms");
	set_short("handful of mushrooms");
	set_long("This is a handful of mushrooms. They are quite " +
	"large. They must have been grown in an extremely fertile " +
	"patch of soil.\n");
	
	add_prop(OBJ_I_WEIGHT, 100); 	
	add_prop(OBJ_I_VOLUME, 50);
	add_prop(OBJ_M_NO_GIVE, "Don't give those away!");
	add_prop(OBJ_M_NO_STEAL, 0);
	add_prop(OBJ_M_NO_SELL, 0);
	add_prop(OBJ_M_NO_DROP, "Don't drop them, someone might step on them!");
}
