#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

void create_component()
{
	add_name("trap");
	add_name("foothold");
	set_adj("foothold");
	set_short("foothold trap");
	set_pshort("foothold traps");
	set_long("Two iron jaws with razor sharp teeth, connected by a trigger mechanism. "+
		"The size of the trap suggests it was designed for catching bears, or other large animals.\n");
	add_prop(OBJ_I_WEIGHT, 2700);
	add_prop(OBJ_I_VOLUME, 1200);
	
	set_component_id("snare");
	set_component_value(2);
	
}
	