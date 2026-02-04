#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

void create_component()
{
	add_name("battery");
	add_name("cube");
	set_adj(({"cubical", "steel"}));
	set_short("@@my_short");
	set_long("@@my_long");
	add_prop(OBJ_I_WEIGHT, 800);
	add_prop(OBJ_I_VOLUME, 400);
	
	set_component_id("battery");
	set_component_value(2);
}
	
string my_short()
{
	if(TP->query_skill(SS_SET_TRAP) > 30)
		return "battery charge";
	return "steel cube";
}

string my_long()
{
	if(TP->query_skill(SS_SET_TRAP) > 30)
		return "Small, cubical battery charge, used in some traps.\n";
	return "Small cube made of steel. Two short wires of misterious purpose are attached "+
		"to it's surface.\n";
}
	