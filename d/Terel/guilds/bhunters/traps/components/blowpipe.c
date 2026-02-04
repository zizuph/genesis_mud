#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";


void create_component()
{
	add_name("blowpipe");
	set_adj(({"long", "wooden"}));
	set_short("long blowpipe");
	set_long("Long blowpipe made of wood. Those are rumoured to be weapon of choice of many "+
		"assasings and bounty hunters around Terel.\n");
	add_prop(OBJ_I_WEIGHT, 20);
	add_prop(OBJ_I_VOLUME, 50);
	
	set_component_id("blowpipe");
	set_component_value(1);
}
