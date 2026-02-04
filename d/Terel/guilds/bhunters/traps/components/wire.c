#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";


void create_component()
{
	add_name("wire");
	set_adj(({"thin", "copper"}));
	set_short("thin copper wire");
	set_long("Thin wire made of copper. It's about 3 feet long and looks very plastic.\n");
	add_prop(OBJ_I_WEIGHT, 800);
	add_prop(OBJ_I_VOLUME, 600);
	
	set_component_id("wire");
	set_component_value(1);
}
	
	