#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

public string query_component_id()
{
	return "paint";
}

public int query_component_value()
{
	return 1;
}

void create_component()
{
	add_name("bucket");
	add_name("paint");
	set_adj(({"wooden"}));
	set_short("bucket of paint");
	set_long("A bucket full of red, intesive smelling paint.\n");
	add_prop(OBJ_I_WEIGHT, 2500);
	add_prop(OBJ_I_VOLUME, 2300);
	
	set_component_id("paint");
	set_component_value(1);
}
	
	