#include <stdproperties.h>

#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

public string query_component_id()
{
	return "shovel";
}

public int query_component_value()
{
	return 2;
}

public int query_multiple_use()
{
	return 1;
}

void create_component()
{
	add_name("shovel");
	set_adj("short");
	add_adj("small");
	set_short("small shovel");
	set_pshort("small shovels");
	set_long("A short, sharp edged shovel of decent quality. It's size makes it very handy, but it would " +
		"tough to dig a large hole with it, not to mention bashing someone on the head.\n");
	add_prop(OBJ_I_WEIGHT, 3000);
	add_prop(OBJ_I_VOLUME, 1000);
	
	set_component_id("shovel");
	set_component_value(2);
	set_multiple_use();
}
	