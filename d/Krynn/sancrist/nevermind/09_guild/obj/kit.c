/* Created by Dajala
 * A heap of parts for the different modules the member can buy and 
 * build the modules from.
 * The 'build' routine is in the soul.
 * 'Attach' is here in the kit.
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"
#include "../modules.h"

string type;
int bomb, built, break_chance, tick_again = 0;

void
create_object()
{
	set_name("heap");
	add_name("heap of parts");
	add_name("kit");
	set_short("heap of parts");
	set_long("This is a heap of a lot of different small tubes, gears, "
		+ "springs and the like.\n@@my_long@@.\n");
	set_adj("small");
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_M_NO_SELL, "You don't want to sell the kit, you want "
		+ "to build a module.\n");
}

string
my_long()
{
	if (GMEMBER(TP))
		return "It seems to be a kit for the " + type + "-module";
	if (TP->query_race_name() == "gnome")
		return "The parts seem to somehow fit into a whole but "
			+ "you cannot guess what";
	return "You cannot imagine what it might be good for";
}

void
set_type(string str)
{
	int i;
	type = str;
	add_name("kit_for_" + type);
	add_name(type);
	for(i=0;i<sizeof(TYPES);i++)
		if (type == TYPES[i]) add_prop(OBJ_I_VALUE, VALUES[i]);
}

string
get_type()
{
	return type;
}

void
set_built()
{
	built = 1;
}

void
init()
{
	ADA("attach");
}

int
attach(string str)
{
	int *flags, i;
	object gizmo;

	if(!built)
		return 0;
	NF("Attach what?\n");
	if(!str)
		return 0;
	NF("You don't have that module.\n");
	if(str != type)
		return 0;

	NF("You already own this module.\n");
	flags = ((gizmo = P("k_gizmo", TP))->query_modules());
	for(i=0;i<sizeof(TYPES);i++)
		if(flags[i] && type == TYPES[i]) return 0;

	NF("There is no space left for this module on your gizmo.\n");
	if(gizmo->query_number_of_modules() > 14)
		return 0;
	write("You attach the module to your gizmo. CLICK!\n"
		+ "You perform a final test and ...\n");
	say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n");
	if(bomb == 1)
	{
		write("But why...? It doesn't work?\n");
		write("Perhaps you put together some parts wrongly?\n");
		bomb = set_alarm(15.0, 5.0, "makes_tick", TP);
		set_alarm(50.0, -1.0, "end_tick", TP, bomb);
		TO->set_no_show(1);
	}
	else
	{
		(P("k_gizmo", TP))->add_module("" + break_chance + C(type));
		write("The " + C(type) + " is ready to use!\n");
		TO->remove_object();
	}
	return 1;
}

void
makes_tick(object player)
{
	string *adj = ({"whirring", "clicking", "unidentifyable", "strange", "weird", "dangerous", "ringing"});
	int a;
	
	if(!tick_again)
		player->catch_msg("Suddenly");
	else
		player->catch_msg("Now");
	a = random(7);
	player->catch_msg(" a " + adj[a] + " noise comes from "
		+ "deep within your gizmo.\n");
	tell_room(E(player), "You hear a " + adj[a] 
		+ " noise, originating from somewhere near " + QTNAME(player)
		+ ".\n", player);
}

void
end_tick(object player, int alarm)
{
	remove_alarm(alarm);
	player->catch_msg("Something fell from your gizmo.\n");
	tell_room(E(player), "Something fell from " + QTNAME(player) 
		+ " to the floor.\n");
	clone_object(GOBJ + "junk.c")->move(E(player));
	player->command("oops");
	TO->remove_object();
}

/* Called from the soul */

void
is_bomb()
{
	bomb = 1;
}

void
set_break_chance(int skill)
{
	if(skill > 0)
		break_chance = 9 - (skill/10);
	if(break_chance < 2)
		break_chance = 2;
}
