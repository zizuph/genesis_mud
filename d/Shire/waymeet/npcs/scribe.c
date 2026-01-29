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

	set_name("anno");
	add_name(({"scribe", "_shire_scribe"}));
	set_title("Bunce, the Scribe of the Shire");
	set_race_name("hobbit");
	set_adj(({"near-sighted", "serious"}));
	set_gender(0);
	set_long(
		"This hobbit writes a lot, so much that his fingers are stained black "
			+ "and he squints almost constantly, as if he's trying to read "
			+ "something that's just out of focus.\n");
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
	add_act("emote thinks about the beauty of letters.");
	add_act("say I love letters.");
	add_act("say All the ladies know I have the finest quill.");
	add_act("say I can scribe your parchment.");
	add_act("emote stretches his hands, which look tight from writing.");

	set_default_answer("@@ask_default@@");
	add_ask( ({"scribe", "write", "compose", "dictate"}), "@@ask_dictate@@");
	
	equip( ({(WAYM_OBJ_DIR + "pen"), (WAYM_ARM_DIR + "h_robe") }));
	
}

void
ask_default()
{
	command("say First buy a parchment.");
	command("point sign");
	command("smile help");
	command("say Then select the paper type.");
	command("say And finally dictate your message.");
}

void
ask_dictate()
{
	command("say Simply <dictate> what you want, and I will write it "
		+ "on the scroll for you.");
	command("show pen");
	command("smile help");
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
   " I'm here to write, not socialize.");
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
}