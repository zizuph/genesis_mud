/*
	*King Kalak
	*Altrus, December 2005
*/
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

#define K_DIR "/d/Shire/aop/"

inherit SHIRE_MONSTER;

void create_shire_monster()
{
	set_name("kalak");
	add_name("_king_kalak");
	set_title("the Sorcerer King");
	add_name("king kalak");
	add_name("king");
	add_adj("powerful");
	add_adj("sorcerer");
	set_race_name("human");
	set_short("powerful sorcerer king");
	set_long("He is an impressive yet frightening sight! This imperious figure is none other than King Kalak, the most feared sorcerer king! It would not be wise to displease this powerful man.\n");
	
	set_gender(0);
	set_appearance_offset(-50);
	set_alignment(0);
	set_stats(({300, 300, 300, 300, 300, 300}));
	add_prop(CONT_I_WEIGHT, 85000);
	add_prop(CONT_I_HEIGHT, 1500);
	add_prop(OBJ_M_NO_ATTACK, "Do you really wish to die slowly and painfully?\n");
	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_introduce(1);
	set_height_desc("extremely tall");
	set_width_desc("of normal width");
	set_skill(SS_AWARENESS,100);
	object arm, wep;
	
	clone_object("/d/Shire/aop/kalak_crown")->move(TO);
	clone_object("/d/Shire/aop/kalak_robe")->move(TO);
	clone_object("/d/Shire/aop/kalak_leg")->move(TO);
	clone_object("/d/Shire/aop/kalak_armour")->move(TO);
	
	command("wear armours");
}

public int introduce_me(string who)
{
	who = lower_case(who);
	if (!interactive(present(who,ENV(TO))))
		return 0;

	int num = random(10);
	
	if(num < 4)
	{
		command("say Greetings, and welcome to my arena.");
		command("say I am King Kalak.");
	}
	
	else if(num > 6)
	{
		command("say I am the Sorcerer King.");
		command("say Welcome to my arena.");
	}
	
	else
	{
		command("say I am Kalak, the Sorcerer King.");
		command("say Enough of these pleasantries, sit and enjoy the fighting!");
	}
	
	return 1;
}
