/*
	*The dark sorcerer who turns elves into orcs
	*Altrus, May 2005
 *
 *  Modification Log: - March 2009 (Gorboth) - added set_living_name()
*/
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

inherit SHIRE_MONSTER;

void create_shire_monster()
{
    set_living_name("sharaburz");
	set_name("sharaburz");
	set_title("the Black Sorcerer");
	add_name("sorcerer");
	set_race_name("human");
	add_adj(({"dark-robed"}));
	set_long("Underneath the dark robe you can barely make out the face of this human, if it is a human. There is an aura of power eminating from him.\n");
	
	set_gender(0);
	set_appearance(-110);
	set_alignment(-1200);
	set_stats(({100, 95, 150, 200, 200, 75}));
	add_prop(CONT_I_WEIGHT,55000);
	add_prop(CONT_I_HEIGHT,800);

	set_skill(SS_DEFENCE, 50);
	set_skill(SS_UNARM_COMBAT, 60);
	
	set_act_time(7);
	add_act("leer");
	add_act("emote gathers his robe and moves to another corner of the room.");
	add_act("emote takes something out from the depths of his robe.");
	add_act("emote checks the fire under the cauldron.");
	
	set_chat_time(9);
	add_chat("Fresh meat for the slaughter, eh?");
	add_chat("Ahhh...Perhaps a little bit more of this herb...yessss.");
	add_chat("I suppose that worthless guard Dargum sent you in here.");
	add_chat("More orcs! That's what he commands, and that's what he gets.");
	add_chat("Hmm...You don't look like you could handle it.");
	
	add_ask(({"orc", "orcs", "guild", "members", "member"}), VBFC_ME("ask_guild_info"));
	add_ask(({"join"}), VBFC_ME("ask_joining"));
	add_ask(({"powers", "sorcery", "condition"}), VBFC_ME("ask_powers"));
	add_ask(({"leave", "leaving", "quit", "quitting"}), VBFC_ME("ask_leaving"));
	
	set_introduce(1);
	
	clone_object("/d/Shire/guild/orc_guild/dark_robe")->move(TO);
	
	command("wear armours");
}

public int introduce_me(string who)
{
	who = lower_case(who);
	if (!interactive(present(who,ENV(TO))))
		return 0;

	command("say My name is not imporant.");
	command("sneer " + who);
	command("say The orcs around here seem to call me Sharaburz. That name will suffice.");
	return 1;
}

string ask_guild_info()
{
	command("say Yes. This is a guild for orcs.");
	command("sneer evil");
	command("say Dare I ask if you want to join?.");
	return "";
}

string ask_joining()
{
	command("say So...You do want to join? Well, there is one condition...");
	command("grumble");
	command("say Unfortunate as it is, my powers of sorcery are limited.");
	command("sigh tired");
	return "";
}

string ask_powers()
{
	command("spit");
	command("say Because of the limits of what I can do, the sorcery I perform must be accompanied by a body with its own natural magic energies, or a body laced with pure evil. In other words, I am forced to use only the bodies of goblins, or those of the hated elves!!");
	command("curse");
	command("say Therefore, if you are of elven blood, and have sufficiently cursed it by your own actions, I can use your body, and twist it into the wretched form of an orc.");
	command("say Or if you are a goblin, I can twist it further.");
	command("say However, I will not simply perform the ritual for the asking, you must beg for it!");
	command("say Read what is engraved upon that plaque first.");
	command("point plaque");
	command("say If you are still willing, then by all means, beg for it!!");
	command("emote laughs with an unnerving malevolence.");
	return "";
}

string ask_leaving()
{
	command("say Ahhh... Can't handle it can you?");
	command("smirk");
	command("say I figured as much.");
	command("say Well, all you have to do is cast off the sorcery that binds you to this form.");
	command("spit");
	return "";
}
