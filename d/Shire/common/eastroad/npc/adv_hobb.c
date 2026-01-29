inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include <stdproperties.h>
#include <ss_types.h>

#define ASKING_FOR_INFO "_is_asking_for_task"

int alarm_id;

create_monster()
{
	if(!IS_CLONE)
		return;
	set_name("merriacod");
	set_race_name("hobbit");
	set_adj("adventuring");
	add_adj("exited");
	set_title("Famous Adventurer of Bags End");
	set_short("exited adventuring hobbit");
	set_long(
		"It's a strong hobbit who obviously is far from home. "+
		"Maybe he is out adventuring? He has some strong hands "+
		"and all covered with hair, even his feets is full of hair "+
		"and that might be the reason to why he has no boots. He sure "+
		"look like one that can give you information.\n");
	add_prop(CONT_I_WEIGHT, 60*1000);
	add_prop(CONT_I_HEIGHT, 90);

	set_stats(({ 40+random(19), 40+random(10), 80, 50+random(5), 40, 100 }));
	set_alignment(120);
	set_skill(SS_WEP_KNIFE, 60);
	set_skill(SS_DEFENCE, 50);
	set_skill(SS_PARRY, 50);
	set_skill(SS_AWARENESS, 60);
	set_skill(SS_LOC_SENSE, 50);
	set_skill(SS_SNEAK, 70);
	set_skill(SS_HIDE, 70);
	set_pick_up(39);
	//set_restrain_path(({"/d/Shire/common/eastroad", "/d/Shire/common/bree"}));
	//set_random_move(6);
	
	set_act_time(6);
	add_act("introduce me");
	add_act(({"time", "say I should find myself some shelter soon."}));
	add_act("smile shy");

	set_chat_time(6);
	add_chat("Hello Mister.");
	add_chat("I have travelled far and wide in this world i tell you.");
	add_chat("Begging you pardon master?");
	add_chat("It sure is scary in these parts.");
	add_chat("I saw some creatures in that forest, what they call it, trollshaws, right?");
	add_chat("Ohh, i am soo hungry, it's been almost 2 hours since my last meal!");
	add_chat("Ask me anything and I'll tell you about it.");	

	set_cact_time(2);
	add_cact("cringe");
	add_cact("drink all");
	add_cact("kick all");
	add_cact(({"sneak n", "hide"}));
	add_cact(({"sneak e", "hide"}));
	add_cact(({"sneak w", "hide"}));
	add_cact(({"sneak s", "hide"}));
	add_cact(({"sneak sw", "hide"}));
	add_cact(({"sneak nw", "hide"}));

	set_cchat_time(2);
	add_cchat("Yeah, tough guy attacking me, a small tiny adventurer eh!!");
	add_cchat("I thought the elves had demolished such folks like you!");
	add_cchat("Help help help a newbie killer!!!");
	
	MAKE_MONEY;
	make_silver(5+random(6));
	add_ask(({"task", "quest", "job","help"}), VBFC_ME("ask_misc"));
}

string
ask_misc()
{
	if(TP->query_prop(ASKING_FOR_INFO))
	{
		command("say I have already told you all i know mister.");
		command("smile all");
		return "";
	}
	else
	{
	command("say hmm, a job you want? Well, i can't help you much there really.");
	command("think");
	command("say But surely i can give you information about places in the area.");
	command("smile");
	TP->add_prop(ASKING_FOR_INFO, 1);
	set_alarm(12.0, 0.0, "more_areas");
		return "";
	}
}

string
more_areas()
{
	command("brighten");
	command("smile shy");
	command("say I have been travelling far abroad i dare say");
	command("say master. But of those places i fear most is the");
	command("say area of Rhudaur say which lie just north of the");
	command("say fearsome Trollshaws. There is said that only ");
	command("say ghosts and evil are present, and nought is left");
	command("say of the good that once dwelled there, or so say");
	command("say Glorfindel, who himself dwell in Rivendell. I");
	command("say have nought been able to locate the path to ");
	command("say Rhudaur yet, but i am in search, and i guess");
	command("say it's only a matter of time before i can find it.");
	command("ponder");
	command("say Of Rivendell i dont have much to say, except that");
	command("say Glorfindel told me, i met him accidentaly near the");
	command("say Trollshaws, yes, well, he told me that it was ");
	command("say closely guarded, and not open for strangers yet,");
	command("say and he warned me to not go tither yet, without ");
	command("say guards or rangers who are known in that area.");
	command("smile");
	command("i really dont have much more to tell you mister. So ");
	command("say long and happy adventuring.");
	command("wave happ all");
	return "";
}

arm_me()
{
	object knife1, knife2, jacket, pants;

	seteuid(getuid());

	knife1 	= clone_object(EROAD_DIR +"wep/lo_knife");
	knife1->move(TO);
	knife2 	= clone_object(EROAD_DIR +"wep/sh_knife");
	knife2->move(TO);
	jacket 	= clone_object(EROAD_DIR +"arm/l_jacket");
	jacket->move(TO);
	pants 	= clone_object(EROAD_DIR +"arm/trouser");
	pants->move(TO);
	command("wear all");
	command("smile");
	command("say It's a cold day isnt it?");
}

void
attacked_by(object obj)
{
	::attacked_by(obj);
	command("say I have fought many a beast on my journeys!");
	command("wield all");
	command("emote enters a fighting position.");

	alarm_id = set_alarm(10.0, 30.0, "before_attack");
}

void
before_attack()
{
	if(TO->query_attack())
		return;
	command("unwield all");
	command("say Phew, this is the last time i go alone!");
	command("sigh relie");
	remove_alarm(alarm_id);
}

