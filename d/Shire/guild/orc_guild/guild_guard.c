/*
	*Orc guard of the orc race guild
	*Altrus, May 2005
*/
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

inherit SHIRE_MONSTER;

void create_shire_monster()
{
	set_name("dargum");
	set_title("the worthless guard");
	add_name("guard");
	set_race_name("orc");
	add_adj(({"short","filthy-smelling"}));
	set_long("This orc has pale grey, green-flecked flesh. He is the guard of the cave entrance, but doesn't look like he is enjoying that job. Although he looks small for an orc, he could probably hold his own in a fight. He looks angry and annoyed.\n");
	
	set_gender(0);
	set_appearance(-90);
	set_alignment(-800 - random(100));
	set_stats(({100, 95, 250, 50, 50, 75}));
	add_prop(CONT_I_WEIGHT,30000);
	add_prop(CONT_I_HEIGHT,500);

	set_skill(SS_DEFENCE, 50);
	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_WEP_SWORD, 50);
	
	set_act_time(7);
	add_act("complain");
	add_act("curse");
	add_act("growl");
	add_act("spit");
	add_act("sulk");
	add_act("emote grumbles aloud about never getting to join the raiding parties.");
	add_act("emote picks up something that was crawling on the floor and eats it.");
	add_act("emote scratches himself on the arm; bits of filth fall on the floor.");
	add_act("emote wonders if anyone weaker will come along and take his place as guard.");
	add_act("emote wipes drool off his chin.");
	
	set_chat_time(9);
	add_chat("I am not snaga!");
	add_chat("I suppose I will have to keep guarding this cave longer.");
	add_chat("Can I at least get something decent to eat! Give me a nice bit o' man flesh, 'tis good for the body!");
	add_chat("Lousy nazgul always telling us what to do... Hey! You didn't hear me say that!");
	add_chat("You looking to start trouble?");
	
	add_ask(({"orc", "orcs", "guild", "members", "member"}), VBFC_ME("ask_guild_info"));
	add_ask(({"join"}), VBFC_ME("ask_joining"));
	add_ask(({"dark lord"}), VBFC_ME("ask_dark_lord"));
	add_ask(({"enemies"}), VBFC_ME("ask_enemies"));
	add_ask(({"nazgul"}), VBFC_ME("ask_nazgul"));
	add_ask(({"elves", "elf"}), VBFC_ME("ask_elves"));
	
	set_introduce(1);
	
	clone_object("/d/Shire/guild/orc_guild/leather_armour")->move(TO);
	
	clone_object("/d/Shire/guild/orc_guild/dented_greaves")->move(TO);
	
	clone_object("/d/Shire/guild/orc_guild/rusty_blade")->move(TO);
	
	command("wear armours");
	command("wield weapons");
}

string ask_guild_info()
{
	command("say Eh? You want to know about the orcs who live here?");
	command("smile evil");
	command("say Well, I ain't gonna tell you much, but we don't go in for those who make life better for the enemies of the Dark Lord. So if you are pure of heart, you best leave now.");
	command("smirk");
	command("say If you think you belong here, I suppose you might be able to join.");
	return "";
}

string ask_joining()
{
	command("say Oh? You want to join us here in the dark underground? Well, I can't help you there, you better talk to the old one, the...human. He'll tell you what needs to be done. Ask him about orcs; perhaps you will get some good information.");
	command("spit");
	command("point east");
	command("say Go on, get outta my sight.");
	return "";
}

string ask_dark_lord()
{
	command("say Of course he never comes here, but sometimes we get messengers from the black land out this way.");
	command("say We do our own thing out here, raiding and such, but if we are summoned, we go.");
	command("say Last time we refused, one of 'them' showed up. You know what I am talking about... a nazgul.");
	command("shudder");
	return "";
}

string ask_enemies()
{
	command("say Our enemies are anyone who attacks us. Mostly we hate elves, and anyone that has anything to do with them.");
	command("grumble");
	return "";
}

string ask_elves()
{
	command("spit");
	command("say Don't talk to me about them!");
	return "";
}

string ask_nazgul()
{
	command("growl");
	command("say Shut yer yap! Don't talk about them around here, you fool!");
	command("say You wanna bring the whole lot of them here? I sure don't.");
	command("say I should never have mentioned them.");
	command("peer fear");
	return "";
}
