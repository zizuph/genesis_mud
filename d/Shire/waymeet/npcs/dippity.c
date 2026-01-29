/* 
 * Proprietor of The Novelty Shop, in Waymeet.
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

	set_name("dippity");
	add_name(({"proprietor", "_novelty_proprietor_"}));
	set_title("Bracegirdle, Novelest Novelty Shop Noveller");
	set_race_name("hobbit");
	set_adj(({"peppy", "curly-haired"}));
	set_gender(1);
	set_long(
		"This hobbit runs the Novelty Shop, which seems like a "
		+ "novel job. Her hair is abnormally curly, even for "
		+ "a hobbit.\n");
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
	add_act("emote rings a cowbell.");
	add_act("emote polishes a large round wheel.");
	add_act("emote reads the sign.");
	add_act("emote shows off her brass token.");

	set_default_answer("@@ask_default@@");
	
}

void
ask_default()
{
	command("say All you have to do is <pay fee>.");
	command("emote smiles wealthily.");
	command("say Then, put your token in the slot and spin "
		+ "the wheel.");
	command("emote goes wheeeeeeeeeeee.");
	command("say And then you get something--dare I say--novel!");
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
   " Welcome to the novelty shop where everything is novel!");
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