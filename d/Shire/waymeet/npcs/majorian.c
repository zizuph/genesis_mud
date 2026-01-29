/* 
 * Proprietor of Ye Olde Fireworks Shoppe, in Waymeet.
 * Raymundo, Feb 2020
 */

inherit "/std/monster";
#include "/d/Shire/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


void return_introduce();
void greet(object ob);

object *inv;

create_monster()
{
	if (!IS_CLONE)
		return;

	set_name("majorian");
	add_name(({"proprietor", "_fireworks_proprietor_"}));
	set_title("Chubb-Baggins, Proprietor of Ye Olde Fireworks Shoppe");
	set_race_name("hobbit");
	set_adj(({"smiley", "singed-eyebrowed"}));
	set_gender(0);
	set_long(
		"This hobbit works at the fireworks shop. "
		+ "He looks like the kind of guy who would sell you small "
		+ "explosive devices. His eyebrows are singed and, if you're "
		+ "honest, nearly burned off.\n");
	default_config_npc(30);
	set_base_stat(SS_DIS, 40);
	set_base_stat(SS_DEX, 40);

	set_skill(SS_UNARM_COMBAT, 30);
	set_skill(SS_DEFENCE, 30);
	set_skill(SS_AWARENESS, 20);
	set_alignment(200 + random(50));

	add_prop(CONT_I_WEIGHT, 60*1000); //100 Kg's.
	add_prop(CONT_I_HEIGHT, 100);		//170 cm tall.
	remove_prop(NPC_M_NO_ACCEPT_GIVE);
	
	set_act_time(20);
	add_act("smile");
	add_act("emote warns you not to light things on fire.");

	set_default_answer("@@ask_default@@");
	
}

void
ask_default()
{
	command("say Buy some fireworks!");
	command("point sign");
	command("smile greed");
	command("say But don't burn your eyebrows off!");
	command("emote touches his eyebrows.");
}

init_living() 
{
   ::init_living();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say to " + ob->query_real_name() + 
   " Welcome to the fireworks shoppe. Would you like to buy "
	+ "anything?");
}

int
add_introduced(string who)
{
   object ob;
   
   if (!who) return 0;
   who = lower_case(who);
   ob = present(who, environment());
   if (!ob) return 0;
   if (!CAN_SEE(this_object(), ob)) return 0;
   if (!notmet_me(ob))
   {
	   command("say to " + TP->query_real_name() 
		+ " So nice to see you again!");
	   return 0;
   }
   
   set_alarm(itof(random(9)),0.0,&return_introduce());
   return 1;
}

void
return_introduce()
{
   command("introduce myself");
}