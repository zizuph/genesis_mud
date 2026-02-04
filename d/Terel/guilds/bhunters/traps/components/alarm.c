#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";


void create_component()
{
	add_name("alarm");
	add_name("clip");
	set_adj(({"small", "metal", "magic"}));
	set_short("@@my_short");
	set_long("@@my_long");
	add_prop(OBJ_I_WEIGHT, 20);
	add_prop(OBJ_I_VOLUME, 10);
	
	set_component_id("alarm");
	set_component_value(1);
}
	
string my_short()
{
	if(TP->query_skill(SS_SET_TRAP) > 30)
		return "magic alarm";
	return "small metal clip";
}

string my_long()
{
	if(TP->query_skill(SS_SET_TRAP) > 30)
		return "A magic alarm, when attached to a trap it notifies the hunter whenever it's triggered.\n";
	return "Small, shiny clip of some kind of metal. You've got no idea what it could be used for.\n";
}
	
public void init()
{
	::init();
	add_action("attach", "attach");
}

int attach(string a)
{
	SEND("alarm: attach");
	SEND(a);
	object trap = E(TP)->my_trap();
	notify_fail("Attach what to what?\n");
	if(!objectp(trap))
		return 0;
	if(a != " to trap" && a!= " to " + trap->query_name() + " trap")
		return 0;
	notify_fail("You can't attach another alarm to this trap.\n");
	int ret = trap->attach_alarm(TO);
	if(ret)
		write("You attach an alarm to the " + query_name() + " trap.\n");
	return ret;
}