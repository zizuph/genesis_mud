#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <stdproperties.h>

inherit BHTRAPS + "trap";

int cAlarm, *dAlarms = ({});

public void create_trap()
{
	configure_trap(500, 800, 350, 9.0, 5.0, "pitfall");
}

string *query_component_list()
{
	return ({"shovel", "shovel", "shovel"});
}

string *query_set_phases()
{
	return ({
			({
				"You take a firm grip on your shovel and start digging a hole in the ground.\n",
				" takes a firm grip on his shovel and starts digging a hole.\n"
			}),
			({
				"You finish diging and look for something to camouflage the pitfall.\n",
				" finishes diging and looks around, as if looking for something.\n"
			})
		});
}

public string *query_disarm_desc()
{
	return ({"You remove the camouflage and fill the pitfall with dirt.\n",
		" removes the camouflage and buries the hole beneath.\n"});
}

public int can_be_placed(object ob)
{
	return 1 - ob->query_prop(ROOM_I_INSIDE);
}

public void remove_object()
{
	for(int i = 0; i < sizeof(dAlarms); ++i)
	{
		if(pointerp(get_alarm(dAlarms[i])))
			return 0;
	}
	spoiled = 1;
	::remove_object();
}

void destun(object ob)
{
	ob->catch_msg("Bruises still hurt as hell, but you feel bit better now.\n");
	ob->remove_stun();
	remove_object();
}

public void trap_me(object ob)
{
	if(pointerp(get_alarm(cAlarm)))
		remove_alarm(cAlarm);
	
	/* mounted players handled later */
	object victim;
	if(ob->is_steed_shadow())
		return;
	if(!ob->query_has_riders())
	{
		ob->catch_msg("\nThe ground suddenly opens under you feet! You trip and bruise yourself "+
			"as you fall into a pitfall trap.\n\n");
		tell_room(E(ob), QCTNAME(ob) + " makes a careless step and falls into a comouflaged pitfall!\n", ob);
		ob->add_stun();
		dAlarms += ({set_alarm(20.0 + rnd() * 10.0, 0.0, &destun(ob))});
		return;
	}
	while(ob->query_has_riders())
	{
		victim = ob->query_driver();
		ob->do_dismount(victim, 1, 1);
		victim->catch_msg("You fall from your steed, bruising yourself badly.\n");
		victim->add_stun();
		dAlarms += ({set_alarm(30.0 + rnd() * 20.0, 0.0, &destun(victim))});
		victim->heal_hp(-1 * (victim->query_prop(OBJ_I_WEIGHT) / 50) + random(100));
		if(victim->query_hp() <= 0)
		{
			if(objectp(find_player(query_owner())))
				victim->do_die(find_player(query_owner()));
			else
				victim->do_die();
		}
	}	
	tell_room(E(ob), QCTNAME(ob) + " collapses as " + ob->query_pronoun() + " falls " +
		" into a pitfall trap.\n", ob);
	move(E(ob));
}

void collapse()
{
	tell_room(E(TO), "You hear wood-creaking sound, and suddenly a shallow pitfall emerges right "+
		"next to you, as its comouflage collapses.\n");
	remove_object();
}

/* This trap disapears by itself after some time */
public void armed_by(object ob)
{
	::armed_by(ob);
	cAlarm = set_alarm(600.0 + rnd() * 600.0, 0.0, &collapse());
}

public string query_set_desc()
{
	if(!query_spoiled())
		return "Carefully camouflaged, 3 feet deep hole in the ground. Shallow pitfalls like this " +
			"are sometimes used in battles to stop cavalery charge.\n";
	return "You can only assume that it supposed to be a pitfall trap, it's just a hole in the ground.\n";
}
