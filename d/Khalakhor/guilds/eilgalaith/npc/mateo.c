/**********************************************************************
 * - junil.c                                                        - *
 * - Mateo trainer for Eil-Galaith garden.c                         - *
 * - Created by Damaris 12/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"

inherit "/d/Khalakhor/std/npc/elf";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

static mapping remembered = ([]), failed = ([]);

string
ask_help()
{
	command("asay smooth If you are worthy, I will help you.");
	command("emote points to the sign.");
	return ""; 
}
string
ask_eilgalaith()
{
	command("asay smooth Perhaps you should go speak with Junil.");
	command("emote points toward the door.");
	return "";
}
string
ask_magic()
{
	command("asay smooth Ahh magic. You wish to know more of magic?");
	command("asay smooth Young one, seek the truth within the "+
	"mystic vine.");
	command("smile thought");
	command("asay smooth There is more to magic than meets the eye. "+
	"You are a bit young, but if you continue along your search you "+
	"will find your way.");
	return "";
}
string
ask_crystal()
{
	command("asay smooth The crystal room is for you to enjoy "+
	"young one.");
	command("emote gestures toward the door.");
	return "";
}
string
ask_coffer()
{
	command("asay smooth The crystal coffer is for you to use.");
	command("smile myster");
	return "";
}
void
create_khalakhor_elf()
{
	set_name("mateo");
	set_race_name("elf");
	add_name("magician");
	set_title("Uluith of the House Uluith");
	set_adj("mysterious");
	add_adj("dark");
	set_gender(G_FEMALE);
	set_long("She is the trainer of magic of Eil-Galaith.\n"+
	"She has peach coloured skin.\n"+
	"She has mysterious dark eyes.\n"+
	"Her hair is hip length, coal black and windswept.\n"+
	"She has the distinguished mark of the mystic vine of the "+
	"Eil-Galaith.\n"+
	"She wears the ruby and ebony colours of an elven House "+
	"Uluith.\n");
	
	set_skill(SS_AWARENESS, 30);
	set_skill(SS_UNARM_COMBAT, 20);
	set_skill(SS_DEFENCE, 20);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_PARRY, 100);
	set_act_time(30);
	set_chat_time(30); /* Interval between chat */ 
	
	add_prop(CONT_I_WEIGHT,48000);
	add_prop(CONT_I_HEIGHT,190);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	set_alignment(900);
	//set_exp_factor(10); 
	set_stats(({ 190, 190, 190, 190, 190, 190 }));
	clone_object(ARM + "mmantle")->move(TO);
	clone_object(ARM + "cloak")->move(TO);
	clone_object(ARM + "mpants")->move(TO);
	clone_object(ARM + "mboots")->move(TO);
	command("wear all");
	
	/* This is the message given when someone asks us about something
	 * we don't know about (anything not defined in add_ask()) */
	 
	 set_default_answer(QCTNAME(TP)+ " mumbles: I do not understand "+
	 "what you are asking. Go bother someone else.\n");
	 add_act("emote gently pulls on the hood of her cloak.");
	 add_act("emote bends down while examining a small flower "+
	 "then rises slowly.");
	 add_ask("help", ask_help);
	 add_ask("eil-galaith", ask_eilgalaith);
	 add_ask("magic", ask_magic);
	 add_ask(({"crystal","crystal room"}), ask_crystal);
	 add_ask(({"crystal coffer", "coffer"}), ask_coffer);

}

/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces themselves
 *                to us.
 * Arguments    : str - Name of the player introducing.
 * Returns      : 1
 */
public int
hook_return_intro(string str)
{
	if (!remembered[str])
	{
		command("say Good day to you, " + capitalize(str) +
		", I'm " + query_name() + " " + query_title() + 
		". A pleasure to meet you.");
		command("bow " + str);
		remembered[str] = "nice";
		present(str, environment(TO))->add_introduced("mateo");
	}
	else if (remembered[str] == "bad")
	{
		command("growl sof");
		command("say I remember you, so if you would be "+
		"on your way!");
	}
	else
	{
		command("giggle");
		command("say Ahh, yes, of course, I remember you from "+
		"your last visit, " + capitalize(str) + ", I hope "+
		"you are doing well?");
	}
	return 1;
}

public void
add_introduced(string who)
{
	hook_return_intro(who);
}

