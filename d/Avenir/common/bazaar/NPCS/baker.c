// file name:     ~Avenir/common/bazaar/NPCS/baker.c
// creator(s):     Lilith, Sept 1999
// last update:
// purpose:     
// note:           
// bug(s):     
// to-do:                  

inherit "/std/monster";
inherit "/d/Avenir/inherit/intro";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"

#define TP  this_player()
#define TO  this_object()

#define BAZ_OBJ "/d/Avenir/common/bazaar/Obj/worn/"

int alarm_id;

void
create_monster()
{
	 string *randadj = ({ "red-faced", "flour-dusted", "plump",
								 "kind", "generous" });
	 if (!IS_CLONE)
		  return;

	 set_name("brinya");
	 set_living_name(query_name());
	 add_name(({"baker", "woman", "female", "server"}));
	 set_race_name("gnome");
	 set_adj(randadj[random(sizeof(randadj))]);
	 set_title("the baker's wife");
	 set_long("She is a woman of middle years, slightly stout "+
		  "and double-chinned.\nHer hair is carefully braided "+
		  "and frames a round face with kind, dark eyes.\n");

	 set_gender(G_FEMALE);
	 add_prop(NPC_I_NO_LOOKS, 1);
	 remove_prop(NPC_M_NO_ACCEPT_GIVE);

	 set_stats(({60, 75, 60, 50, 50, 40}));
	 set_skill(SS_AWARENESS, 50);
	 set_skill(SS_DEFENCE, 50);
	 set_skill(SS_WEP_CLUB, 40);
	 set_alignment(0);

	 set_act_time(5);
	 add_act("smile cheer");
	 add_act("smile helpful");
	 add_act("say My bryndons are particularly good.");

	 add_ask(({"city","forbidden city"}),
			"say The Forbidden City is the island where the Shadow Elves "+
			"live. It is a marvellous place. For those permitted to enter, "+
			"it is a great honour.",1);
	 add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
		  "say We of Sybarus are the Faithful. We live to serve and "+
		  "uphold the Pact, that the Source will always cast its illum"+
		  "ination upon us.",1);
	 add_ask(({"infidel","infidels", "prisoner", "prisoners",
		  "criminals"}), "say A most unpleasant question. I hope "+
		  "that you do not plan to pursue this topic?", 1);


}

void
equip_me()
{
	 seteuid(getuid());
	 clone_object(BAZ_OBJ + "worn/blouse")->move(this_object());
	 clone_object(BAZ_OBJ + "worn/tousers")->move(this_object());
	 command("wear all");
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with.
 */
void
check_meet(object tp)
{
	 string  occ;
	 int     i = random(10);

	 if (!present(tp, environment(TO)))
		  return;

	if(tp->query_prop("_is_cat_"))
	{
		command("say This is no place for flea-infested animals!");
		command("emote wields a broom");
		return;
	}


	 if (IS_INFIDEL(tp))
	 {
		  command("emote points south");
		  command("say to "+ tp->query_real_name() +" Filthy "+
				"law-breakers are not welcome here.");
		  command("say Leave, else I will fetch the guards.");
		  return;
	 }
	 occ = tp->query_guild_name_occ();
	 if (occ == OUNION)
	 {
		  if (i == 2)
				command("cutsey deep "+ tp->query_real_name());
		  if (i == 4)
				command("say to "+ tp->query_real_name() +" I am "+
					 "honoured by your presence!");
		  return;
	 }
}

void
init_living()
{
	 ::init_living();

	 if (interactive(TP) && CAN_SEE(TO, TP))
	 {
		  if (alarm_id)
				return;
		  else
				alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
	 }
}


/*
 * Function name: return_hug
 * Description  : When the NPC is hugged, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_hug(object actor, string adverb)
{
	 /* Player is no longer in the room with us, or even no longer in the
	  * game.
	  */
	 if (!objectp(actor) ||
	(environment(actor) != environment()))
	 {
	return;
	 }

	 command("smile slight "+ OB_NAME(actor));
	 command("say Demonstrations of affection are quite nice, but they "+
		  "don't pay my bills.");
}
/*
 * Function name: return_hit
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_hit(object actor, string adverb)
{
	 /* Player is no longer in the room with us, or even no longer in the
	  * game.
	  */
	 if (!objectp(actor) ||
	(environment(actor) != environment()))
	 {
	return;
	 }

	 command("frown "+ OB_NAME(actor));
	 command("say I will refuse you service if youdo that again.");
	 command("say If beating women is your pleasure, visit the Ziggurat "+
		  "in the Forbidden City...");
	 command("say They take all kinds there...even yours.");
	 command("spit");
}

/*
 * Function name: return_grope
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_grope(object actor, string adverb)
{
	 /* Player is no longer in the room with us, or even no longer in the
	  * game.
	  */
	 if (!objectp(actor) ||
	(environment(actor) != environment()))
	 {
	return;
	 }

	 /* Do the stuff. */
	 command("smile ");
	 command("say to "+ OB_NAME(actor) +" You should go see "+
		  "Qalita.");
}

/*
 * Function name: return_poke
 * Description  : When the NPC is poked, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_poke(object actor, string adverb)
{
	 /* Player is no longer in the room with us, or even no longer in the
	  * game.
	  */
	 if (!objectp(actor) ||
	(environment(actor) != environment()))
	 {
	return;
	 }

	 /* Do the stuff. */
	 command("poke " + OB_NAME(actor));
	 command("say You must be a friend of Tricky's.");
	 command("say Any friend of Tricky's is welcome, he used to spend a " +
	"lot of gold watching me dance.");
}

/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 */
void
emote_hook(string emote, object actor, string adverb)
{
	 /* See if we want to trigger on the emote. If so, call a little alarm
	  * for the reaction function.
	  */
	 switch(emote)
	 {
		  case "caress":
		  case "grope":
		  case "fondle":
		  case "lick":
				set_alarm(3.0, 0.0, &return_grope(actor, adverb) );
				return;

		  case "poke":
		 set_alarm(3.0, 0.0, &return_poke(actor, adverb) );
		 return;
		  case "hug":
		  case "kiss":
		  case "cuddle":
		  case "snuggle":
				set_alarm(3.0, 0.0, &return_hug(actor, adverb));
				return;
		  case "slap":
		  case "kick":
				set_alarm(3.0, 0.0, &return_hit(actor, adverb));
				return;
	 }
}

