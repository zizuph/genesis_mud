#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <language.h>
#include <tasks.h>
#include <ss_types.h>

inherit "/std/shadow";

object trap = 0;

/* returns one if there is a trap in this location */
public int have_trap();
public object my_trap();

public void enter_inv(object ob, object from)
{
	shadow_who->enter_inv(ob, from);
	if(!living(ob))
		return;
	if(objectp(trap))
	{
		trap->trigger(ob);
		trap->spots(ob);
	}
}

public string long(string str)
{
	if(stringp(str))
		return shadow_who->long(str);
	return shadow_who->long(str) + 
		(objectp(trap) ? trap->query_add_short(TP) : "");
}

public void remove_shadow()
{
	shadow_who->remove_item("trap");
	shadow_who->remove_item(trap->query_name() + " trap");
	::remove_shadow();
}

public void set_me(object new_trap)
{
	trap = new_trap;
	/* It's devided so players can't check if there is a trap here by typing 'exa <anything> trap' */
	shadow_who->add_item("trap", "@@desc_trap1");
	shadow_who->add_item(trap->query_name() + " trap", "@@desc_trap2");
}

string desc_trap1()
{
	if(trap->query_spoted(TP))
		return trap->query_set_desc();
	return "You find no trap.\n";
}

string desc_trap2()
{
	if(trap->query_spoted(TP))
		return trap->query_set_desc();
	return "You find no " + trap->query_name() +" trap.\n";
}

public object my_trap()
{
	return trap;
}

public int have_trap()
{
	return 1;
}