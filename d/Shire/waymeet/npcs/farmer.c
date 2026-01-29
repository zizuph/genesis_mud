/* 
 * A farmer.
 * Raymundo, March 2020
 */

inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define OUTSIDE "_i_can_go_out_back"

void return_introduce();
void greet(object ob);

object *inv;

create_monster()
{
	if (!IS_CLONE)
		return;

	set_name("reginard");
	add_name(({"farmer"}));
	set_title("Longhole, the Tobacco Farmer");
	set_race_name("hobbit");
	set_adj(({"pipe-smoking", "pot-bellied"}));
	set_gender(0);
	set_long(
		"He looks like the kind of hobbit who would enjoy a good meal or "
		+ "three and then a long smoke.\n");
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
	add_act("say You really need to let tobacco cure.");
	
		
	

	set_default_answer("@@ask_default@@");
	add_ask(({"help", "quest", "task", "aid"}), "@@ask_quest@@");
	add_ask( ({"wolf", "wolves"}), "@@ask_wolf@@");
	add_ask( ({"reward"}), "@@ask_reward@@");
	add_ask( ({"tobacco", "letter", "crate", "letter of requisition", "tobacco crate"}),
		"@@ask_letter@@");
}

void
ask_letter()
{
	object letter;
	object *inv;
	 int i = 0;
	 inv = all_inventory(this_player());
	 for (i=0; i<sizeof(inv); i++)
	 {
		 if(inv[i]->id("_letter_of_requisition_"))
		 {
			TP->add_prop(OUTSIDE, 1);
			write("You give your letter to the farmer.\n");
			say(QCTNAME(TP) + " gives a letter to the farmer.\n");
			command("say Well... let me see here...");
			command("emote mumbles under his breath.");
			command("emote mutters.");
			command("say Everything seems to be in order here. Go "
				+ "out back and get yourself a crate of tobacco from "
				+ "the shed.");
			command("emote tucks the letter into his pocket.");
			command("say I'll keep the letter if you don't mind. I need to "
				+ "be sure I get paid.");
			inv[i]->remove_object();
			return;
		 }
		 if(TP->query_prop(OUTSIDE))
		 {
			 command("say Yes, yes. You already gave me a letter. Go "
				+ "out to the shed get yourself a crate of tobacco.");
			return;
		 }
		 else
		 {
			 command("say You need a letter of requisition before I'll let "
				+ "you just wander around my curing shed!");
			return;
		 }
	 }
}

void
ask_reward()
{
	command("say Reward? What for? Did you harvest the tobacco? No! "
		+ "I did! So I'm the one who gets the reward.");
		return;
}
	 

void
ask_quest()
{
	command("say I don't have any quests for you. I just grow "
		+ "tobacco and cure it in my shed out back.");
		return;
}

void
ask_wolf()
{
	command("say There are wolves around.");
	command("say You can feel free to kill them.");
	command("grin .");
	return;
}

void
ask_default()
{
	command("say Folks from all over Middle Earth want my Pipeweed. It's "
		+ "the best.");
		return;
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
   command("say to " + ob->query_nonmet_name() + 
   " Welcome to my farmhouse. The wolves' howling drives me crazy!");
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
	   command("say to " + TP->query_nonmet_name() 
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
   command("bow");
}