/*
  Caravan clerk, quest giver for caravan protection quest.
    by Udana, 03/06
    Modified with some acts by Pasqua 04/06
*/

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>

#define CARAVAN_START SILVER_DIR + "road/road02"
#define PLAYER_I_DEFENDED_CARAVAN "_player_i_defended_caravan"


inherit STDMONSTER;

string caravan_first_answer();
string caravan_second_answer();

public void create_terel_monster()
{
	set_name("clerk");
	set_adj("busy");
	set_short("busy clerk");
	set_long("A man behind the desk seems to be completely "+
		"involved in his job. He barely notices anything but "+
		"documents he's looking at.\n");
	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_default_answer("The clerk ignores your question focusing on his papers.\n");
	set_act_time(5 + random(5));   

	add_act("emote studies some of the papers on the marble table.");
	add_act("emote whispers something to the receptionist.");
	add_act("say Caravan needs more protection.. ");
	add_act("emote walks up to one of the bookcases and studies some filed reports.");
	add_act("emote notes something down quickly.");
	add_act("emote starts to discuss something with the receptionist.");
	add_act("say If only we had more men.");
	
	add_ask(({"caravan", "help", "task", "quest"}), "@@caravan_first_answer");
	add_ask(({"guards", "more guards", "protection", "caravan protection", 
                "defend", "danger", "great danger"}), 
            "@@caravan_second_answer");
	add_ask("reward", "@@reward_quest");
}

string reward_quest()
{
	if(!TP->query_prop(PLAYER_I_DEFENDED_CARAVAN))
	{
		command("say I'll reward you when you do what I asked you to do.");
		return "";
	}
	TP->remove_prop(PLAYER_I_DEFENDED_CARAVAN);
	command("say Yes, I heard caravan made it safely to the Last, here "+
		"is your reward.");
	MONEY_MAKE_GC(100)->move(TP);
	if(!TP->test_bit("Terel", QUEST_CARAV_GROUP, QUEST_CARAV_BIT))
	{
		if(TP->query_exp() <= QUEST_CARAV_REWARD ) 
			TP->add_exp_quest(TP->query_exp());
		else
			TP->add_exp_quest(QUEST_CARAV_REWARD);
		write("You feel more experienced.\n");
		TP->set_bit(QUEST_CARAV_GROUP, QUEST_CARAV_BIT);
		write_file(QUEST_LOG, capitalize(TP->query_real_name()) +
			" defended the caravan (" + ctime(time()) + ")\n");
	}
	return "";
}
		

string caravan_first_answer()
{
	FIX_EUID;
	if(TP->test_bit("Terel", QUEST_CARAV_GROUP, QUEST_CARAV_BIT))
	{
		command("say You have helped us a lot already, thank you.");
		return "";
	}
	if(TP->query_alignment() < 0)
	{
		command("say You seem more like a bandit then a guard to me. Be gone!");
		return "";
	}
	command("say Yes, we are indeed in need of more guards for caravan protection. You could help defend it, though there may be great danger.");
	return "";
}

string caravan_second_answer()
{
	FIX_EUID;
	if(TP->test_bit("Terel", QUEST_CARAV_GROUP, QUEST_CARAV_BIT))
	{
		command("say You have helped us a lot already, thank you.");
		return "";
	}
	if(TP->query_alignment() < 0)
	{
		command("say You seem more like a bandit then a guard to me. Be gone!");
		return "";
	}
	if(!(CARAVAN_START)->create_caravan(TP))
	{
		command("say The caravan is currently on it's way through "+
			"the forest. I doubt you can catch it now. Come back "+
			"later.");
		return "";
	}
	command("say The caravan is currently assembling just north of the Calathin "+
		"gates. Go there and you might still catch it.");
	return "";
}

/*
 * I spared myself inheriting preancient std_citizen, yet I still want to
 * have this guy be one. The below function is copied from
 * /d/Terel/calathin/std_citizen.c
 * originally by Shinjo.
 */

#define KILLS_CAL "_kills_cal"


void
do_die(object killer)
{
    int i;
    object *enemies;

    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    for (i=0; i<sizeof(enemies); i++)
    {
        if(enemies[i]->query_prop(KILLS_CAL) > 6)
        {
            object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
            kill_logger->add_killer(enemies[i]->query_name());
        }
        enemies[i]->add_prop(KILLS_CAL,
                           enemies[i]->query_prop(KILLS_CAL) + 1);
    }
    if(killer->query_prop(KILLS_CAL) > 6)
    {
        object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
        kill_logger->add_killer(killer->query_name());
    }
    killer->add_prop(KILLS_CAL,
                       killer->query_prop(KILLS_CAL) + 1);
    ::do_die(killer);
}


