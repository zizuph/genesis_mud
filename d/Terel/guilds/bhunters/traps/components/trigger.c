#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

public string query_component_id()
{
	return "trigger";
}

public int query_component_value()
{
	return 1;
}

void create_component()
{
	add_name("mechanism");
	add_name("trigger-mechanism");
	set_adj("small");
	set_short("trigger-mechanism");
	set_long("This small, yet complicated mechanism is used in all various kinds of " +
		"traps.\n");
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 50);
	
	set_component_id("trigger");
	set_component_value(1);
	
}
	
	