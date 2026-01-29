/**********************************************************************
 * - dromadus.c                                                     - *
 * - Dromadus trainer for Eil-Galaith training room                 - *
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
	command("say You look like you could use help.");
	command("chuckle");
	command("emote points to the sign.");
	return ""; 
}
string
ask_eilgalaith()
{
	command("eyebrow inquis");
	command("say Eil-Galaith?");
	command("say Are you sick or something? This is Eil-Galaith. "+
	"Go talk to Junil. He enjoys chatting.");
	command("emote points towards the door.");
	command("say Don't waste my time.");
	return "";  
}
void
create_khalakhor_elf()
{
	set_name("dromadus");
	set_race_name("elf");
	add_name("trainer");
	set_title("Xelith of the House Xelith");
	set_adj("muscular");
	add_adj("gruff");
	set_gender(G_MALE);
	set_long("He is the trainer of Eil-Galaith.\n"+
	"He has light tan skin.\n"+
	"He has piercing dark blue eyes.\n"+
	"His hair is shoulder length, raven black and "+
	"tied at the neck.\n"+
	"He has the distinguished mark of the mystic vine of the "+
	"Eil-Galaith.\n"+
	"He wears the crimson and gold colours of an elven House "+
	"Xelith.\n");
	
	set_skill(SS_AWARENESS, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_WEP_POLEARM, 100);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_PARRY, 100);
	set_act_time(30);
	set_chat_time(30); /* Interval between chat */ 
	add_prop(CONT_I_WEIGHT,50000);
	add_prop(CONT_I_HEIGHT,200);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	set_alignment(900);
	//set_exp_factor(10);
	set_stats(({ 180, 180, 180, 180, 180, 180 }));
	clone_object(WEP + "trident")->move(TO);
	command("wield weapon");
	clone_object(ARM + "dmantle")->move(TO);
	clone_object(ARM + "doublet")->move(TO);
	clone_object(ARM + "pants")->move(TO);
	clone_object(ARM + "mboots")->move(TO);
	command("wear all");
	
	/* This is the message given when someone asks us about 
	 * something we don't know about (anything not defined in
	 * add_ask()) */
	 
	 set_default_answer(QCTNAME(TP)+" gruffly says: What? Oh go ask "+
	 "someone else.\n");
	 add_act("emote suddenly swings the silver and gold trident "+
	 "in the air then smiles.");
	 add_act("emote quickly spins around practicing with the silver "+
	 "and gold trident.");
	 add_ask("help", ask_help);
	 add_ask("eil-galaith", ask_eilgalaith);
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
		present(str, environment(TO))->add_introduced("dromadus");
	}
	else if (remembered[str] == "bad")
	{
		command("growl mena");
		command("say I remember you, so if you would be on "+
		"your way!");
	}
	else
	{
		command("chuckle");
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

