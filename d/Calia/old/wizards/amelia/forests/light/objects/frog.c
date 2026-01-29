/*
*   by Amelia, for use in the Light Forest, frog pond
*/
inherit "std/object";
#include <stdproperties.h>
#include <macros.h>

int id;
object TP = this_player();
object TO = this_object();

create_object()
	{
	set_name("frog");
	add_name("bullfrog");
	add_name("jeremiah");
	set_short("large green bullfrog");
	set_pshort("large green bullfrogs");
	set_long("A large green bullfrog. He looks like he might be "+
		"hard to catch.  \nHe looks philosophical.\nHe's "+
		"feeling very well.\n");
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_I_WEIGHT, 50);
	add_cmd_item(({"frog","bullfrog"}), "kiss", "@@kiss_me");
	add_cmd_item(({"frog","bullfrog"}),"kill", "@@kill_me");
	add_cmd_item(({"frog","bullfrog"}),"get", "@@no_get");
	add_cmd_item("all", "get", "@@no_get");
	add_cmd_item(({"frog","bullfrog"}), "take", "@@no_get");
	add_cmd_item(({"frog","bullfrog"}),"catch", "@@catch_frog");
	add_prop(OBJ_I_VOLUME, 50);

	}

void
enter_env(object ob, object from)
{

	::enter_env(ob,from);
	if (interactive(ob))
	id = set_alarm(10.0, 45.0, "croak", ob);
}

void
leave_env(object ob, object to)
{

	::leave_env(ob,to);
	if(interactive(ob))
	{
	remove_alarm(id);
	id = set_alarm(5.0,0.0, "hop_away");
	}
}

int
croak(object ob)
{
	tell_room(environment(ob),"Ribbit! Ribbit!\n",({}));
}

int
hop_away(object ob)
{

seteuid(getuid(TO));
	if (TO!=TP)
	TO->remove_object();
	tell_room(environment(TP), "The frog leaps quickly away.\n", ({}));
	
}

int
kiss_me()
{
		write("You kiss the frog, and he kisses you back!\n");
		tell_room(environment(TP), QCTNAME(TP)+" gently "+
		"kisses the frog.\n",({TP}));
		return 1;
}

int
kill_me()
{
	object dummy;
	write("The frog makes a giant leap!\n");
	TO->hop_away(dummy);
	return 1;
}

int
no_get()
{
	tell_room(environment(TP), QCTNAME(TP)+ " tries to "+
		"get the frog, but fails.\n", ({TP}));
	write("You try to get the frog, but he's too slippery "+
		"to catch with your bare hands.\n");
	return 1;
}

int
catch_frog()
{

	object n = present("net", TP);

	if (objectp(n))
		{
		if (TP==n->query_wielded())
		{
		write("You catch the frog with the net!\n");
		TO->move(TP);
		tell_room(environment(TP), QCTNAME(TP)+
		" catches the frog deftly with "+
		TP->query_possessive()+" net.\n", ({TP}));
		return 1;
		}
		else
		{
		notify_fail("But you're not wielding the net!\n");
		return 0;
		}
	}

	else
		notify_fail("The frog is too slippery. You "+
		"can't catch him with your bare hands.\n");
		return 0;

}
