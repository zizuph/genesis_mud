inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/goodkill.h"
#include "/d/Shire/imladris/guild/guild.h"
#include "/d/Shire/bits.h"

#define QUEST_NAME 			"missing_jewel"
#define LW_SOUL 			"/d/Shire/imladris/spell/lw/lw"
#define CW_SOUL				"/d/Shire/imladris/spell/cw/cw"
#define HEALER_SOUL_FILE	"/d/Shire/imladris/guild/soul"

#define QUEST_NR_1		"_quest_nr_1"
#define QUEST_NR_2		"_quest_nr_2"
#define QUEST_NR_3		"_quest_nr_3"
/* Prototypes */
string give_task(); //give this quest
void quest_var_1();
void quest_var_2();
void quest_var_3();
void reward_missing_quest(object who);
void start_quest_1();
void start_quest_2();
void start_quest_3();


int alarm_id;

create_monster()
{
	if(!IS_CLONE)
		return;
	
	set_name("glorfindel");
	set_adj("white-haired");
	add_adj("elegant");
	set_title("Lord of Imladris");
	set_race_name("elf");
	set_gender(G_MALE);
	set_long(
		"This is one of the mighty elves who dwell in Rivendell, or Imladris as "+
		"the elves prefer to call it. He looks tall and fair, a proud elven warrior. It looks "+
		"he is guarding the ford for evil creatures. He is an elf of legends "+
		"having fought many a battle during the ages. He is old, but yet he looks quite "+
		"young. Tales tell that the elves of Rivendell possess great magic, and are also "+
		"known for being great warriors.\n");

	set_learn_pref(({ 0,0,0,1,1,1 }));

	set_stats(({120+random(20),130+random(20),120+random(20), 220, 230, 100}));
	set_alignment(700 +random(300));
	MAKE_MONEY;
	make_platinum(2+random(4));
	make_gold(6+random(10));

	set_base_stat(SS_OCCUP, query_average_stat()+random(20));
	
	set_skill(SS_WEP_SWORD, 		 90);
	set_skill(SS_2H_COMBAT, 		 90);
	set_skill(SS_DEFENCE, 			 70);
	set_skill(SS_PARRY, 			 70);
	set_skill(SS_AWARENESS, 		 70);
	set_skill(SS_SPELLCRAFT, 		100);
	set_skill(SS_ELEMENT_EARTH,		 80);
	set_skill(SS_ELEMENT_LIFE, 		 80);
	set_skill(SS_ELEMENT_FIRE, 		 80);
	set_skill(SS_FORM_CONJURATION, 	 80);
	set_skill(SS_FORM_ABJURATION, 	 80);
	set_skill(SS_FORM_DIVINATION, 	 90);

	remove_prop(NPC_M_NO_ACCEPT_GIVE);
	add_prop(CONT_I_WEIGHT, 100*1000);
	add_prop(CONT_I_HEIGHT, 190);
	add_prop(LIVE_I_SEE_DARK, 20);
	//add_prop(LIVE_I_QUICKNESS, 10);

	add_subloc("_special_look", TO);
	
	set_chat_time(4);
	add_chat("Sshhh...I thought I heard something.");
	add_chat("Those foul riders are abroad again.");
	add_chat("Elrond would appreciate some help.");
	add_chat("Have you seen the sword?");
	add_chat("Imladris is luckily safe right now.");
	add_chat("Elrond is watching the river.");

	trig_new("%w 'introduces' %s", "react_introduce");
	add_ask(({"task", "sword", "anduril", "elrond", "quest", "job", "help", 
	"light", "assignment"}), VBFC_ME("give_task"));

	set_alarm(0.5,0.0, "arm_me");
}

void
arm_me()
{
	//object robe, mail, boots, sword, greav, brac;
	//::arm_me();
	seteuid(getuid());
	//robe = clone_object(RIV_DIR +"arm/elf_robe");
	//robe->move(TO);
	//mail = clone_object(RIV_DIR +"arm/elf_mail");
	//mail->move(TO);
	//boots = clone_object(RIV_DIR +"arm/elf_boot");
	//boots->move(TO);
	//greav = clone_object(RIV_DIR + "arm/e_greave");
	//greav->move(TO);
	//sword = clone_object(RIV_DIR +"wep/gl_sword");
	//sword->move(TO);
	add_cmdsoul(HEALER_SOUL_FILE);
	add_cmdsoul(LW_SOUL);
	add_cmdsoul(CW_SOUL);
	update_hooks();
	//command("wear mail");
	//command("wear boots");
	//command("wear robe");
	//command("wield sword");
	command("smile");
}

chk_health()
{
	if(query_hp() < query_max_hp())
	{
		tell_room(ENV(TO), 
		"Sings an ancient elven hymne. He seems to gain new strength from the song.\n");
		heal_hp(700);
		add_mana(2500);
		add_panic(-1000);
	}
}

int
filter_enemy(object who)
{
	return (who->query_attack() == TO);
}

/*
int
special_attack(object enemy)
{
	object *victim = ({});
	
	victim = filter(all_inventory(ENV(TO)), "filter_enemy", TO);
	if (!random(4))
		victim = ({enemy});
	else
		victim = ({ victim[random(sizeof(victim))] });

	switch(random(4))
	{
	case 0:
		command("are on "+victim);
		break;
	case 1:
		command("kalya on "+victim);
		break;
	case 2:
		command("rilma on "+victim);
		break;
	case 3:
		command("silme aure");
		break;
	}
	return 1;
}
*/
int
react_introduce(string who, string dummy)
{
	if (who)
	{
		who = lower_case(who);
		call_out("return_introduce", 3, who);
		return 1;
	}
}

void
return_introduce(string who)
{
	object ob;
	int		i;

	if(ob = present(who, environment()))
	{
		i = random(3);
		if (i == 0)
		{
			command("say Greetings in the name of Elrond, the half-elven, true Lord of Rivendell.");
			command("say Have you come to aid Elrond in these perilious times? Give a helping hand.");
			command("introduce me");
			command("Elrond have a task for you, which I can offer.");
		}
		else if (i == 1)
		{
			command("shake "+who);
			command("introduce me");
			command("say Welcome "+CAP(who)+", is there anything I can help you with?");
			command("smile serious "+who);
		}
		else if (i ==2)
		{
			command("introduce me");
			command("say Greetings "+CAP(who)+".");
			command("say And what is your business here so close to Imladris?");
		}
	}
}

#define GUILD_TAX 35

int
query_guild_tax_occ()
{
	return GUILD_TAX;
}

string
query_guild_style_occ()
{
	return GUILD_STYLE;
}

string
query_guild_name_occ()
{
	return GUILD_NAME;
}

query_guild_title_occ()
{
	return "High White star of Imladris";
}

int
query_spell_level()
{

	return 25;
}

int
spell_list_exp()
{
	return 1000000;
}

string
show_subloc(mixed subloc, object me, object who)
{
	if(who==me)
		return "You are one of the High Elven Lords, a Master Healer of Imladris.\n";
	else
		return "He is a High Elven Lord, a Master Healer of Imladris.\n";
}

int
query_knight_prestige()
{
	return -30;
}

string
give_task()
{
	int r;
	r = random(3);	

	if(!TP->test_bit("Shire", EASTERN_GROUP, IMLADRIS_SWORD_BIT))
	{
		if(TP->query_prop(QUEST_NR_1))
		{
			quest_var_1();
			return "";
		}
		else if(TP->query_prop(QUEST_NR_2))
		{
			quest_var_2();
			return "";
		}
		else if(TP->query_prop(QUEST_NR_3))
		{
			quest_var_3();
			return "";
		}
		else
		switch(r)
		{
			case 0:
				quest_var_1();
				return "";
			case 1:
				quest_var_2();
				return "";
			case 2:
				quest_var_3();
				return "";
		}
	}
	else
	{
		command("say Sorry, but i have no need for your service at this time.");
		return "";
	}

}

void
quest_var_1()
{
	if(TP->query_prop(QUEST_NR_1))
	{
		command("smile "+TP->query_name());
		command("say You have all the information you need.");
		command("say GO now with haste, and find what we need!");
		return;
	}
	command("say Othar, the esquire of Isildur saved the shards from");
	command("say Elendil's sword in the slaughter on the Gladden Fields.");
	command("say The sword was broken and the light in it was extinguished.");
	command("say Elrond percieved that it would take many years before it");
	command("say  would be reforged anew.");
	command("sigh");
	command("say But when Master Elrond and his great elven smiths started");
	command("say to reforge the sword for the Dunedain, the heir of Isildur");
	command("say they discovered that the sword missed one piece, which was");
	command("say vital for the sword to shine. A small jewel which once the");
	command("say trees of Valinor shone upon. Unless we can find that jewel");
	command("say again, the sword will never shine upon the face of");
	command("say Middle-Earth ever. It was a jewel that the Noldor which");
	command("say dwelt in Valinor mined, a very precious jewel it is.");
	command("sniff"); 
	command("say The jewel was with the shards Othar carried with him, and");
	command("say it was lost when he walked through the mines of Moria.");
	command("say Rumours have it that he was attacked by dwarves there, as");
	command("say they lusted for the great jewel. We doubt that, since we");
	command("say don't think the dwarves are of such kind. Othar himself");
	command("say lived only a few days after he returned to Imladris and we");
	command("say could not get the whole story out of him.");
	command("ponder");
	command("say I urge you to go out and search for the jewel. A great");
	command("reward will be granted to you if you can find the jewel and");
	command("say return it here to me.");
	TP->add_prop(QUEST_NR_1, 1);
	start_quest_1();
}

void
start_quest_1()
{
	object obj;
	obj = clone_object(IML_DIR +"obj/narsil_jewel");
	obj->move(array[random(sizeof(QUEST_ROOMS_1) - 1)]);
	return;
}

void
reward_missing_quest(object who)
{
	if(who->query_prop(QUEST_NR_1))
	   who->remove_prop(QUEST_NR_1);
	else
	if(who->query_prop(QUEST_NR_2))
	   who->remove_prop(QUEST_NR_2);
	else
	if(who->query_prop(QUEST_NR_3))
	   who->remove_prop(QUEST_NR_3);

	who->set_bit(EASTERN_GROUP, MISSING_JEWEL_QUEST);
	who->add_exp(MISSING_JEWEL_EXP, 0);
	seteuid(getuid(TO));
	log_file(QUEST_NAME, extract(ctime(time()), 4, 15)+" "+	
	CAP(who->query_real_name())+" rewarded with "+MISSING_JEWEL_EXP+" exp, "+
	"<"+who->query_average_stat()+"> avg stats.\n");
	tell_object(who, "You feel much more experienced!\n");
	say(QCTNAME(who)+" got a nice reward.\n");
}

