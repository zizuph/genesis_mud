/* 
 * A farmer.
 * Questmaster for /d/Shire/private/QUESTS/kill_wolves.txt
 * Raymundo, March 2020
 * 
 */

inherit "/std/monster";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define WOLF "_i_did_wolves_"

void return_introduce();
void greet(object ob);

object *inv;

create_monster()
{
	if (!IS_CLONE)
		return;

	set_name("boso");
	add_name(({"farmer"}));
	set_title("Galbassi, the Farmer");
	set_race_name("hobbit");
	set_adj(({"grumpy", "hairy-footed"}));
	set_gender(0);
	set_long(
		"He is a grumpy looking bachelor farmer.\n");
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
	add_act("say Those damn wolves!");
	add_act("grumble");
	add_act("say If only someone would kill the wolves. It's hard "
		+ "for me to pick vegetables without getting attacked!");
	add_act("emote thinks about those wolves.");
	add_act("say Can you help me with the wolves, please?");
	add_act("emote picks some meat out of his teeth.");
	add_act("say I don't understand why women dislike this house. I "
		+ "think it's nice--and I made it myself!");
		
	

	set_default_answer("@@ask_default@@");
	add_ask(({"help", "quest", "task", "aid"}), "@@ask_quest@@");
	add_ask( ({"wolf", "wolves"}), "@@ask_wolf@@");
	add_ask( ({"reward"}), "@@ask_reward@@");
}

void
ask_reward()
{
	if(CHECK_QUEST(TP, "wolves")) //can't redo the quest.
	{
		command("say I've already given you your reward!");
		command("say But thanks for killing the wolves for me!");
		command("smile");
		return;
	}
	else //we count how many pelts there are
		object *inv;
	 int i = 0;
	 int pelt = 0;
	 inv = all_inventory(this_player());
	 
	 for (i=0; i<sizeof(inv); i++)
	 {
		 if(inv[i]->id("_waymeet_wolf_pelt"))
		 {
			 pelt ++;
		 }
		 
	 }
	 if(pelt >= 10) //you get your reward if there are enough
	 {
		 command("say You killed the wolves for me! Thanks!");
		 for(i = 0; i<sizeof(inv); i++)
		 {
			 if(inv[i]->id("_waymeet_wolf_pelt"))
			 {
				 inv[i]->remove_object(); //remove all the pelts
			 }
		 }
		 write("You feel more experienced!\n");
		 REWARD_QUEST(TP, "wolves"); //give qxp
		 
		 return;
	 }
	 if(pelt == 1)
	 {
		 command("say You only killed one mangy grey wolf. I need ten pelts!");
		 command("say I hate wolves!");
		 return;
	 }
	 else
	 {
		 command("say You only brought me " + pelt + " pelts!\n");
		 command("say I need ten!");
	 return;
	 }
}
	 

void
ask_quest()
{
	if(CHECK_QUEST(TP, "wolves"))
	{
		command("say You've already helped me so much. Thanks!");
		command("bow " + TP->query_real_name());
		return;
	}
	else
	{
		command("say Wolves! They're a meance!");
		command("grumble");
		command("say They've been attacking me when I've gone to work "
			+ "in my fields!");
		command("say I need you to kill ten mangy grey wolves and bring me back "
			+ "their pelts as proof. Can you do that? When you have "
			+ "ten pelts just come back and ask me for a reward.");
		command("shout Not just any wolf, mind you, but the mangy grey wolves "
            + "from the fields near Waymeet. "
			+ "I WANT THEM DEAD!");
		command("smile thank");
		return;
	}
}

void
ask_wolf()
{
	command("say The wolves keep attacking me. I need them dead.");
	command("shout DEAD!");
	command("emote smiles bloodthirstily.");
	return;
}

void
ask_default()
{
	command("say These wolves are a major problem. Can you help me please?");
	command("smile hope");
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

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    command("say Just ask for a reward. No need to hand things over like this.");
    command("drop all");
}