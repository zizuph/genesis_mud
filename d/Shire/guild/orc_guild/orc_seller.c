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
	set_name("ashpar");
	set_title("the slaughterer");
	set_race_name("orc");
	add_adj(({"long-armed","gore-covered"}));
	set_long("This orc is completely covered in fresh blood and gore. He has a wide grin of enjoyment on his broad face; he seems to love his job.\n");
	
	set_gender(0);
	set_appearance(-100);
	set_alignment(-1000 - random(100));
	set_stats(({130, 125, 250, 50, 50, 75}));
	add_prop(CONT_I_WEIGHT,36000);
	add_prop(CONT_I_HEIGHT,700);

	set_skill(SS_DEFENCE, 50);
	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_WEP_KNIFE, 50);
	
	set_act_time(6);
	add_act("grumble");
	add_act("swear");
	add_act("growl");
	add_act("spit");
	add_act("emote cuts some meat into thin strips.");
	add_act("emote rips a haunch off one of the carcasses.");
	add_act("emote spits in the water basin.");
	add_act("emote hacks into the side of horse carcass, splattering blood all over.");
	add_act("emote wipes drool off his chin.");
	
	set_chat_time(8);
	add_chat("If ya wants meat and gots money, I can help!");
	add_chat("Nothin' like orc liquor when you're needin' to drink.");
	add_chat("Don't let me catch you givin' food to that lousy Dargum. He ain't guardin' the entrance because he likes bein' there.");
	add_chat("If I hear one more complaint about da bread...");
	add_chat("Don't just stand there, order somethin'!");
	
	add_ask(({"bread", "haunch", "entrails", "meat", "food", "water", "brew", "strange brew", "liquor", "orc liquor", "drinks", "drink"}), VBFC_ME("ask_food"));
	add_ask(({"dargum"}), VBFC_ME("ask_dargum"));
	
	set_introduce(1);
	
	clone_object("/d/Shire/guild/orc_guild/leather_armour")->move(TO);
	
	clone_object("/d/Shire/guild/orc_guild/bloody_cleaver")->move(TO);
	
	clone_object("/d/Shire/guild/orc_guild/long_blade")->move(TO);
	
	command("wear armours");
	command("wield weapons");
}

string ask_food()
{
	command("spit");
	command("point sign");
	return "";
}

string ask_dargum()
{
	command("say That lazy lout? He was caught thieving from my liquor stash!");
	command("curse");
	command("say If you're a friend of his, leave.");
	command("point west");
	return "";
}
