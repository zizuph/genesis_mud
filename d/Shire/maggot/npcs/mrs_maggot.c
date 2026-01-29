/*
	*Mrs. Maggot
	*Altrus, April 2005
 *
 * 2005/04/04 Last update
 * 2011/08/06 Lavellan - Improved names/adjs
 * Cotillion - 2020-09-29
 * - Fixed type confusion
 */
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

#define WEED_QUEST "weeds"
#define MUSH_QUEST "mushroom"
#define WEED_PROP "_picking_weeds"
#define MUSH_PROP "_gathering_mushrooms"
#define WEED_ONE "_weed_garden_one"
#define WEED_TWO "_weed_garden_two"
#define WEED_THREE "_weed_garden_three"
#define WEED_FOUR "_weed_garden_four"
#define MUSHROOM_PROP "_already_picked_mushrooms"
#define ARM_DIR "/d/Shire/maggot/arm/"
#define WEP_DIR "/d/Shire/maggot/wep/"

inherit SHIRE_MONSTER;

void create_shire_monster()
{
	set_name("marigold");
	set_title("Maggot");
	//add_name("mrs. maggot");
    add_name("maggot");
	set_race_name("hobbit");
	add_adj(({"red-faced","flustered"}));
    add_name("mrs");
    add_name("mrs.");
    add_adj("mrs.");
    add_adj("mrs");
	set_long("This must be the hard-working hobbit-wife of the house. She appears very busy, bustling about the kitchen preparing food.\n");

	set_gender(1);
	set_appearance(80);
	set_alignment(200 + random(100));
	set_stats(({50, 60, 30, 70, 70, 20}));
	add_prop(CONT_I_WEIGHT,30000);
	add_prop(CONT_I_HEIGHT,500);

	set_skill(SS_DEFENCE, 50);
	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_WEP_CLUB, 50);

	set_act_time(5);
	add_act("@@bustle");
	add_act("stretch");
	add_act("complain");
	add_act("smell");

	set_chat_time(6);
	add_chat("If only I had time to weed my flower garden!");
	add_chat("Do you think you could help me?");
	add_chat("Where is that husband of mine? I need those mushrooms.");

	add_ask(({"task","quest","help"}), VBFC_ME("ask_quest_info"));
	add_ask(({"weed","garden","flower garden"}), VBFC_ME("ask_weeds"));
	add_ask(({"mushrooms","husband","maggot", "cooking"}), VBFC_ME("ask_mushrooms"));
	add_ask(({"reward", "for reward", "for a reward"}), VBFC_ME("weeds_reward"));

	set_introduce(1);

    equip(({
    	ARM_DIR + ({"blouse_c", "blouse_p", "blouse_w"})[random(3)],
    	ARM_DIR + ({"skirt_p", "skirt_w"})[random(2)],
    	ARM_DIR + ({"apron_f", "apron_w"})[random(2)],
    	WEP_DIR + ({"m_roller", "m_pan"})[random(2)],
    }));
}

int bustle()
{
	say(QCTNAME(TO) + " bustles about the kitchen.\n");
	return 1;
}

public int introduce_me(string who)
{
	who = lower_case(who);
	if (!interactive(present(who,ENV(TO))))
		return 0;

	command("say Oh, hello there. You may call me Mrs. Maggot.");
	command("smile politely " + who);
	command("say I could really use some help here.");
	return 1;
}

string ask_quest_info()
{
	command("say I could really use some help. I need someone to weed my garden, and I need some mushrooms for my cooking.");
	return "";
}

string ask_weeds()
{
	if (TP->query_prop(MUSH_PROP))
	{
		command("say But you are already working on something for me!");
		return "";
	}

	if (TP->query_prop(WEED_PROP))
	{
		command("say I already told you! I am too busy to weed my flower garden today, but it really needs doing. Please help me by weeding it for me.");
		return "";
	}

	if (CHECK_QUEST(TP, WEED_QUEST))
	{
		command("say Thanks, but you've already pulled enough weeds for me.");
		return "";
	}

	command("say My garden needs to be weeded, but I haven't the time today. Please, could you be a dear and weed it for me? If you do, I will reward you as best I may.");
	command("say Just come back here and ask me for a reward when you are finished.");
	TP->add_prop(WEED_PROP, 1);
	return "";
}

string ask_mushrooms()
{
	if (TP->query_prop(WEED_PROP))
	{
		command("say But you are already working on something for me!");
		return "";
	}

	if (TP->query_prop(MUSH_PROP))
	{
		command("say I already told you! I really need some mushrooms, and that husband of mine was supposed to bring me some. Go find out why he hasn't brought me any, or at the very least go find me some mushrooms yourself. He should be out in his field somewhere.");
		return "";
	}

	if (CHECK_QUEST(TP, MUSH_QUEST))
	{
		command("say Thank you kindly, but you gathered mushrooms for me already.");
		return "";
	}

	command("say I need some mushrooms for a dish I am making. Mr. Maggot was supposed to bring me some, but I haven't seen him for a while.");
	command("say If you would be so kind, could you find Mr. Maggot for me and ask him where my mushrooms are? Or at least you could find some mushrooms for me yourself.");
	command("say If you can, bring some mushrooms back to me and ask me for a reward.");
	TP->add_prop(MUSH_PROP, 1);
	return "";
}

string weeds_reward()
{
	object shrooms;

	shrooms = present("_maggot_mushrooms", TP);

	if(TP->query_prop(WEED_PROP))
	{
		if(TP->query_prop(WEED_ONE) && TP->query_prop(WEED_TWO) && TP->query_prop(WEED_THREE) && TP->query_prop(WEED_FOUR))
		{
			command("say Thank you very much for weeding my garden! You are a sweetie!");
			TP->remove_prop(WEED_ONE);
			TP->remove_prop(WEED_TWO);
			TP->remove_prop(WEED_THREE);
			TP->remove_prop(WEED_FOUR);
			TP->remove_prop(WEED_PROP);
			TP->catch_msg("You feel more experienced!\n");
			say(QCTNAME(TP) + " was rewarded.\n");
			REWARD_QUEST(TP, WEED_QUEST);
			return "";
		}

		else
		{
			command("say But you haven't finished weeding my garden, dear.");
			return "";
		}
	}

	else if(TP->query_prop(MUSH_PROP))
	{
		if(TP->query_prop(MUSHROOM_PROP))
		{
			command("say Thank you so much for bringing me these mushrooms! They are perfect!");
			TP->catch_msg("You give the mushrooms to Mrs. Maggot.\n");
			say(QCTNAME(TP) + " gives some mushrooms to the flustered hobbit.\n");
			command("smile thankfully");
			TP->catch_msg("You feel more experienced!\n");
			say(QCTNAME(TP) + " was rewarded.\n");
			REWARD_QUEST(TP, MUSH_QUEST);
			TP->remove_prop(MUSH_PROP);
			shrooms->remove_object();
			return "";
		}

		else
		{
			command("say Where are my mushrooms? Did he not have any?");
			return "";
		}
	}

	else
	{
		command("say Reward you for what? I haven't asked you to do anything.");
		return "";
	}
}
