/**********************************************************************
 * - deheune.c                                                      - *
 * - Deheune is the npc that teaches young ladies to become         - *
 * - temptresses.                                                   - *
 * - Created by Damaris@Genesis 4/2006                              - *
 **********************************************************************/
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"
#include "/d/Khalakhor/sys/basic.h";

inherit "/d/Khalakhor/std/npc/human";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
inherit JOIN;
static mapping remembered = ([]), failed = ([]);

void
create_khalakhor_human()
{
	set_name("deheune");
	set_race_name("human");
	add_name("temptress");
	set_title(", devoted follower of Oenghus");
	set_adj("stunningly");
	add_adj("beautiful");
	set_gender(G_FEMALE);
	set_long("She looks like a goddess of love.\n"+
	"She has silky peach coloured skin.\n"+
	"She has mysterious sultry eyes.\n"+
	"Her hair is hip length, strawberry blond with voluptuous "+
	"curls.\n"+
	"She glows with feminine enticement.\n");
	
	set_skill(SS_AWARENESS, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_PARRY, 100);
	set_act_time(30);
	set_chat_time(30); /* Interval between chat */ 
	
	add_prop(CONT_I_WEIGHT,68000);
	add_prop(CONT_I_HEIGHT,190);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	
	set_appearance_offset(-150);
	set_random_move(10);
	set_restrain_path(ROOM);
	
	//set_exp_factor(10); 
	set_stats(({ 190, 190, 190, 190, 190, 190 }));
	
	clone_object(ARM + "gown")->move(TO);
	clone_object(ARM + "sandals")->move(TO);
	clone_object(ARM + "bangles")->move(TO);
	clone_object(ARM + "necklace")->move(TO);
	clone_object(ARM + "circlet")->move(TO);
	command("wear all");
	create_temptress();	
	/* This is the message given when someone asks us about something
	 * we don't know about (anything not defined in add_ask()) */
	 
	 set_default_answer(QCTNAME(TP)+ " sensually purrs: I do not "+
	 "understand what you are asking of me, come recline and enjoy "+
	 "all that the Otherworld offers.\n");
	 add_act("emote gently straightens the edge of her gown.");
	 add_act("emote slowly picks a grape from a vine and slowly "+
	 "slips it in her mouth with a knowing smile.");

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
		command("emote enticingly purrs: Good day to you, "+
		"" + capitalize(str) +", I'm " + query_name() + ""+
		"" + query_title() + ". A pleasure to meet you.");
		command("bow " + str);
		remembered[str] = "nice";
		present(str, environment(TO))->add_introduced("deheune");
	}
	else if (remembered[str] == "bad")
	{
		command("purr sof");
		command("emote enticingly purrs: I remember you, so if "+
		"you would be on your way!");
	}
	else
	{
		command("giggle");
		command("emote enticingly purrs: Ahh, yes, of course, "+
		"I remember you from your last visit, "+
		"" + capitalize(str) + ", I hope "+
		"you are doing well?");
	}
	return 1;
}

public void
add_introduced(string who)
{
	hook_return_intro(who);
}


public void
init_living()
{
    ::init_living();
    init_temptress();
}
