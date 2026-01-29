/*
 * Herbalist for the Thwil herb shop
 * Ckrik 9/2003
 * Fix me: Add Wizard of Roke specials and spells
 */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <composite.h>
#include "/d/Earthsea/quest_handler/quest_handler.h"
#include "defs.h"
inherit "/d/Earthsea/lib/intro";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/std/monster";

#define TASK_ASK (({"task", "about task", "job", "about job", "help"}))
#define SHARK_ASK (({"shark", "white shark"}))
#define PLAYER_I_GOT_GINSENG_TOUR "_player_i_got_ginseng_tour"
#define GINSENG_BOUGHT_HERE "_ginseng_bought_here"

private string give_ginseng_tour();
private int reward_ginseng_tour(object berry, object player);
private int return_stuff(object ob, object player);

void create_earthsea_monster()
{
	set_name("olin");
	set_race_name("human");
	set_living_name("_herbalist_");
	set_title("of Havnor, Senior Wizard Apprentice");
	add_name("herbalist");
	add_name("apprentice");
	add_adj(({"energetic", "bright-eyed"}));
	set_gender(G_MALE);
	set_height("normal length");
	set_width("lean");
	set_long("A energetic bright-eyed apprentice of the Wizard's " +
			"School of Roke. He is one of the older apprentices " +
			"and more seasoned in the arts of Roke wizardry. " +
			"Master Herbal has put him in charge of the " +
			"school's herb store.\n");
	add_prop(OBJ_M_NO_ATTACK, QCTNAME(this_object()) + " looks at you " +
			"strangely, and you feel suddenly embarrassed.\n");
	add_prop(OBJ_M_NO_MAGIC_ATTACK, "Your spell is dissipated by the magic " +
			"cast in this room.\n");
	add_ask(TASK_ASK, VBFC_ME("respond_task_ask"));
	//add_ask(SHARK_ASK, VBFC_ME("respond_shark_ask"));
	set_default_answer(QCTNAME(this_object()) + " says: I don't understand "+
			"your question.\n");
	add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
	set_stats(({100, 140, 100, 145, 145, 140}));
	set_all_hitloc_unarmed(50);
	set_hp(query_max_hp());
	set_skill(SS_DEFENSE, 60);
	set_skill(SS_PARRY, 50);
	set_skill(SS_WEP_POLEARM, 90);
	set_skill(SS_UNARM_COMBAT, 80);
	set_skill(SS_AWARENESS, 35);
	set_skill(SS_BLIND_COMBAT, 50);
	set_alignment(1000);
	set_act_time(50);

	add_act("bounce");
	add_act("emote casts a spell and fireworks appear behind him.");
	add_act("say Roke magic is the oldest and most respected " +
			"in all the realms.");
	add_act("say Wizards trained by Roke serve different lands all " +
			"throughout the realms.");
	add_act("emote studies a forked root carefully.");
}

public string
respond_task_ask()
{
	object note, tp = this_player();

	if (QH_QUERY_QUEST_COMPLETED(tp, "ginseng_tour"))
	{
		command("ask "+ lower_case(tp->query_name()) + " " +
				"Hmm... I think you have helped me before, but thanks "+
				"just the same!");
		command("smile know");
		return "";
	}
	return give_ginseng_tour();
}

public string
respond_shark_ask()
{
	object note, tp = this_player();

	if (QH_QUERY_QUEST_COMPLETED(tp, "ginseng_tour"))
	{
		command("whisper " + lower_case(tp->query_name()) + " " +
				"I over heard from the Archmage that the shark was " +
				"once a wizard that was obsessed with finding a powerful " +
				"giant sword that sank to the bottom of the sea with its " +
				"owner.");
		command("whisper " + lower_case(tp->query_name()) + " " +
				"He never found the sword and now roam the Inmost Sea " +
				"as a white shark.");
		return "";
	}
	command("whisper " + lower_case(tp->query_name()) + " " +
			"Hmm... do a small task for me and I'll tell you more about " +
			"that shark swimming in the bay.");
	return "";
}

public void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);
	if(interactive(from) && (ob->query_herb_name() == "ginseng") &&
			from->query_prop(PLAYER_I_GOT_GINSENG_TOUR))
	{
		set_alarm(2.0, 0.0, &reward_ginseng_tour(ob, from));
		return;
	}
	if(interactive(from))
		set_alarm(2.0, 0.0, &return_stuff(ob, from));

	return;
}

private int
return_stuff(object ob, object player)
{
	command("give "+ ob->query_name() + " to "+
			lower_case(player->query_name()));
	command("say No, thank you.");
	return 1;
}

private string
give_ginseng_tour()
{   
	object note, tp = this_player();
	if(tp->query_prop(PLAYER_I_GOT_GINSENG_TOUR))
	{
		command("ask "+ lower_case(tp->query_name()) + " "+
				"Did you manage to find something?");
		return "";
	}

	tp->add_prop(PLAYER_I_GOT_GINSENG_TOUR, 1);
	command("whisper "+ lower_case(tp->query_name()) + " "+
			"Hmm... I'm a bit low on ginseng. The Archmage will not like that. " +
			"Find me a ginseng and I'll reward you appropriately.");
	return "";
}

private int
reward_ginseng_tour(object ginseng, object player)
{
	if (ginseng->query_prop(GINSENG_BOUGHT_HERE))
	{
		command("say You bought that one from me. I need you to find me " +
				"a fresh one from the forest.");
		command("give "+ ginseng->query_name() + " to "+
				lower_case(player->query_name()));
		return 1;
	}
	player->remove_prop(PLAYER_I_GOT_GINSENG_TOUR);
	command("say Excellent!");

	if(!QH_QUERY_QUEST_COMPLETED(player, "ginseng_tour"))
	{
		command("thank "+ lower_case(player->query_name()));
		QH_QUEST_COMPLETED(player, "ginseng_tour");
		player->remove_prop(PLAYER_I_GOT_GINSENG_TOUR);
		player->catch_tell("You feel a little more experienced!\n");
	}

	return 1;
}
