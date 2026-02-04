#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";


void create_component()
{
	add_name("dart");
	set_adj(({"small", "feathered"}));
	set_short("feathered dart");
	set_long("Short throwing dart. The sharp looking point seems to be covered with some sort of "+
		"liquid.\n");
	add_prop(OBJ_I_WEIGHT, 20);
	add_prop(OBJ_I_VOLUME, 10);
	
	set_component_id("dart");
	set_component_value(2);
}
