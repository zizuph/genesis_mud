#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

void create_component()
{
	add_name("chain");
	set_adj(({"long", "steel"}));
	set_short("steel chain");
	set_long("6 feet long, steel chain, made of tempered, high quality steel. "+
		"It looks very durable.\n");
	add_prop(OBJ_I_WEIGHT, 3200);
	add_prop(OBJ_I_VOLUME, 1000);
	
	set_component_id("chain");
	set_component_value(1);
}
	
	