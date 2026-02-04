#include <stdproperties.h>
#include "../../bhunters.h"
inherit TRAP_COMPONENTS + "component.c";

string size;

public mixed query_component_info()
{
	return size;
}

public int query_component_value()
{
	if(size == "small")
		return 1;
	if(size == "medium")
		return 2;
	return 3;
}

public void set_size(string str)
{
	size = str;
	add_prop(OBJ_I_WEIGHT, query_component_value() * 30000);
	add_prop(OBJ_I_VOLUME, query_component_value() * 7000);
}

void create_component()
{
	add_name("ball");
	set_adj("iron");
	set_short("@@my_short");
	set_long("@@my_long");
	set_size("medium");
	set_component_id("ball");
}
	
string my_short()
{
	return size + " iron ball";
}

string my_long()
{
	return " A simple, round, iron ball, similar to those you can see at prison. This particular one is " +
		(size == "heavy" ? "very heavy" : "of " + size + " size") + ".\n";
}