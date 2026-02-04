#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit BHTRAPS + "trap";

public void create_trap()
{
	configure_trap(600, 800, 800, 2.0, 15.0, "pepper-spray");
}

string *query_component_list()
{
	return ({"trigger", "pepper"});
}

string *query_set_phases()
{
	return ({
			({
				"You hide the trigger-mechanism on the ground.\n",
				" hides something small and shiny.\n"
			})
		});
}

public string *query_disarm_desc()
{
	return ({"You disable the trigger mechanism, and pick it up.\n",
		" disarms a pepper-spray trap.\n"});
}

public void trap_me(object ob)
{
	FIX_EUID;
	ob->catch_msg("\nYou hear a metalic 'click', and suddenly a cloud of black powder fills the room.\n\n");
	tell_room(E(ob), QCTNAME(ob) + " looks down as if he heared something, suddenly a cloud of some " +
		"black powder fills the room.\n", ob);
	object *targets = FILTER_LIVE(all_inventory(E(ob)));
	object blind_obj;
	int def_mod, dex_mod;
	for(int i = 0; i < sizeof(targets); ++i)
	{
		def_mod = 100 - (targets[i]->query_skill(SS_DEFENCE) / 2) - random(50);
		dex_mod = (300 - (targets[i]->query_stat(SS_DEX) / 2) - random(150)) / 3;
		blind_obj = clone_object(BHTRAPS + "blind_obj");
		blind_obj->set_time(def_mod + dex_mod);
		blind_obj->move(targets[i]);
	}
}

public string query_set_desc()
{
	if(!query_spoiled())
		return "A sophisticated triggering mechanism is connected to small steel can.\n";
	return "You assume this trap is supposed to spray pepper in victim's eyes, but it's obviously unfinished.\n";
}