#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <stdproperties.h>
#include <ss_types.h>

inherit BHTRAPS + "trap";

int dAlarm, craft_penality;

public void create_trap()
{
	configure_trap(600, 800, 350, 9.0, 5.0, "electric shock");
}

string *query_component_list()
{
	return ({"wire", "battery"});
}

string *query_set_phases()
{
	return ({
			({
				"You set the battery, and connect it to the wire.\n",
				" connects a wire to strange cubical item.\n"
			}),
		});
}

public string *query_disarm_desc()
{
	return ({"You disarm the battery and detach the wire.\n",
		" disconnects wire from strange cubical item.\n"});
}

public int can_be_placed(object ob)
{
	return 1 - ob->query_prop(ROOM_I_INSIDE);
}

void remove_effects(object ob)
{
	ob->catch_msg("You takes few deep breaths and realize effects of the electric shock are wearing off.\n");
	ob->set_skill_extra(SS_SPELLCRAFT, craft_penality);
	remove_object();
}

public void trap_me(object ob)
{
	int mana_left = (ob->query_mana() / 2) +
		((ob->query_mana() * (ob->query_magic_res(OBJ_I_RES_ELECTRICITY))) / 200);
	ob->set_mana(mana_left);
	craft_penality = (300 - ob->query_stat(SS_STR))
		+ (50 -  ob->query_magic_res(OBJ_I_RES_ELECTRICITY));
	int time_mod = craft_penality;
	craft_penality /= 10;
	if(craft_penality < 0)
		craft_penality = 0;
	if(craft_penality > ob->query_skill(SS_SPELLCRAFT))
		craft_penality = ob->query_skill(SS_SPELLCRAFT);
	ob->set_skill_extra(SS_SPELLCRAFT, - 1 * craft_penality);
	dAlarm = set_alarm(60.0 + rnd() * 60.0 + itof(time_mod), 0.0, &remove_effects(ob));
	move(E(ob));
	ob->catch_msg("\nA sudden shock go through your entire body, the weird, you can smell an "+
		"ozon in the air.. You feel you're loosing your sences.\n\n");
	tell_room(E(ob), QCTNAME(ob) + " hisses in pain and staggers.\n");
}


public string query_set_desc()
{
	if(!query_spoiled())
		return "A wire running cross the path, connected to a strange cubical thing.\n";
	return "A wire running cross the path, connected to a strange cubical thing.\n";
}
