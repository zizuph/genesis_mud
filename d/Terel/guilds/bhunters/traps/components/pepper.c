#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

void create_component()
{
	add_name("container");
	add_name("pepper");
	set_adj(({"small", "steel"}));
	set_short("pepper container");
	set_long("A small steel can containing pepper. It's all smooth and looks impossible to open. " +
		"Some kind of red-labeled pin has been added on its top.\n");
	add_prop(OBJ_I_WEIGHT, 200);
	add_prop(OBJ_I_VOLUME, 100);
	
	set_component_id("pepper");
	set_component_value(2);
	
	add_item(({"pin", "red-labeled pin", "safety-pin"}), "Just a small piece of steel, attached to the steel can. It " +
		"looks like if you could remove it, yet something tells you not to...\n");
}
	
public void init()
{
	::init();
	add_action("remove_pin", "remove");
	add_action("remove_pin", "detach");
}

int remove_pin(string a)
{
	notify_fail(capitalize(query_verb()) + " what?\n");
	if(a != "pin" && a != "red-labeled pin" && a != "safety-pin")
		return 0;
	write("Better not. What if it's going to blow up?\n");
	return 1;
}