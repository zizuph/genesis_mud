/*
	*Rosemary, one of the Maggot daughters (name made up)
	*Altrus, April 2005
*/
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

#define KNOW_NAME	"_know_rosemary_name"
#define BEADS_QUEST	"beads"
#define BRACE_PROP 	"_finding_bracelets_beads"
#define ARM_DIR 	"/d/Shire/maggot/arm/"
#define FIXED_PROP	"_fixed_broken_bracelet"

inherit SHIRE_MONSTER;

void create_shire_monster()
{
	set_name("rosemary");
	set_title("Maggot");
	set_race_name("hobbit");
	add_adj(({"curly-haired","fidgety"}));
	set_long("This small hobbit child looks quite worried about something, and seems unable to stop fidgeting.\n");

	set_gender(1);
	set_appearance(80);
	set_alignment(200 + random(100));
	set_stats(({40, 60, 30, 55, 55, 15}));
	add_prop(CONT_I_WEIGHT,15000);
	add_prop(CONT_I_HEIGHT,300);

	set_skill(SS_DEFENCE, 40);
	set_skill(SS_UNARM_COMBAT, 45);

	set_act_time(5);
	add_act("sigh .");
	add_act("worry");
	add_act("fret");
	add_act("fidget");

	set_chat_time(6);
	add_chat("Oh dear, oh dear. What am I to do?");
	add_chat("Mama will be so upset with me.");
	add_chat("If she finds out, it'll be the wooden spoon for me.");
	add_chat("What am I to do? WHAT am I to do?");

	add_ask(({"task","quest","help"}), "@@ask_quest_info");
	add_ask(({"bracelet"}), "@@ask_bracelet");
	add_ask(({"beads"}), "@@ask_beads");
	add_ask(({"play", "played", "places"}), "@@ask_places");
	add_ask(({"reward", "for reward", "for a reward"}), "@@bracelet_reward");

	set_introduce(1);

    equip(({
    	ARM_DIR + ({"blouse_c", "blouse_p", "blouse_w"})[random(3)],
    	ARM_DIR + ({"skirt_p", "skirt_w"})[random(2)],
    	ARM_DIR + ({"apron_f", "apron_w"})[random(2)],
    }));
}

public int introduce_me(string who)
{
	who = lower_case(who);
	if (!interactive(present(who,ENV(TO))))
		return 0;

	command("say Oh, hi. My name is Rosemary.");
	command("sniff");
	TP->add_prop(KNOW_NAME, 1);
	return 1;
}

string ask_quest_info()
{
	if(CHECK_QUEST(TP, BEADS_QUEST))
	{
		command("say You already helped me once before, I couldn't ask you to help me again.");
	}

	else if(TP->query_prop(BRACE_PROP))
	{
		command("say But you are already helping me! Don't make me explain it all again.");
		command("sob");
	}

	else
	{
		command("say I don't know if you can help me. They are gone. I lost them.");
		command("fret");
		command("say I dropped them and now my bracelet is ruined!");
	}
	return "";
}

string ask_bracelet()
{
	if (TP->query_prop(BRACE_PROP))
	{
		command("say Please don't ask me to explain it all again!");
		command("cry");
		return "";
	}


	if (CHECK_QUEST(TP, BEADS_QUEST))
	{
		command("say You already helped me once before, I couldn't ask you to help me again.");
		return "";
	}

	command("say It had beads on it. They spelled my name. I lost some, and I can't find them!");
	command("sob");
	command("say Please find them. If you do, please string them back onto my bracelet.");
	clone_object("/d/Shire/maggot/obj/broken_bracelet.c")->move(this_player());
	write("The hobbit hands you a broken bracelet.\n");
	TP->add_prop(BRACE_PROP, 1);
	return "";
}

string ask_beads()
{
	if (CHECK_QUEST(TP, BEADS_QUEST))
	{
		command("say You already helped me once before, I couldn't ask you to help me again.");
		return "";
	}

	command("say I lost them. I must have dropped them when I was playing earlier.");
	command("say I already checked in all the places I played, but maybe I didn't look well enough.");
	command("sigh");
	command("say My mother gave the bracelet to me. The beads spelled my name.");
	command("say If you find them, string them all back onto the bracelet. If you fix it, ask me for a reward. I'll find some way to pay you if I can.");
	return "";
}

string ask_places()
{
	if(CHECK_QUEST(TP, BEADS_QUEST))
	{
		command("say You already helped me once before, I couldn't ask you to help me again.");
	}

	else
	{
		command("say Well, I played in Mama's garden in front of the house, and then I played out on the lane by the gate, but Mama saw me and made me come back to the yard, so I played inside the barn until Papa's helpers made me leave.");
		command("fret");
		command("say That was when I noticed my bracelet was gone! I found it, but it only had a few beads left on it.");
		command("sob");
	}
	return "";
}

string bracelet_reward()
{
	object bracelet;

	bracelet = present("_quest_bracelet", TP);

	if(TP->query_prop(BRACE_PROP))
	{
		if(TP->query_prop(FIXED_PROP))
		{
			command("say Thank you so much! How did you ever manage to find all the beads!");
			TP->catch_msg("You hand the bracelet to Rosemary.\n");
			say(QCTNAME(TP) + " hands a bracelet to the hobbit.\n");
			TP->remove_prop(FIXED_PROP);
			bracelet->remove_object();
			TP->catch_msg("You feel more experienced!\n");
			say(QCTNAME(TP) + " was rewarded.\n");
			REWARD_QUEST(TP, BEADS_QUEST);
			return "";
		}

		else
		{
			command("say But my bracelet isn't fixed yet!");
			command("cry");
			return "";
		}
	}

	else
	{
		command("say Reward you for what? I haven't asked you to do anything.");
		return "";
	}
}
