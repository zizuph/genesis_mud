#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>

inherit M_FILE
inherit "/std/combat/humunarmed.c";

int hammer_flag;	/* flag whether a hammer has been lent already */

void
create_krynn_monster()
{
	add_prop(LIVE_I_ALWAYSKNOWN, 1);
	add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
	set_name("aron");
	set_long(
		"Aron, the toolmaster, is in charge of the gnomes' toolstore. "
		+ "He stands behind the counter waiting who asks him for "
		+ "tools to borrow. He smiles at you friendly.");

	set_race_name("gnome");
	set_adj("vivid");
	add_adj("bearded");
	enable_reset(90);

	add_act(({"bow", "say Greetings!", "smile", "say DidArmavirSendYouToMe" 
		+ "ToHelpYou?","emote walks to the shelves.", "emote starts "
		+ "to clean some tools.","emote examines the tools expertly.",
		"emote polishes some tools.","emote has finished cleaning the "
		+ "tools."}));
	set_act_time(30);
	
	add_ask( ({"sign" ,"help" ,"assistance"}), VBFC_ME("sign_check"),1);
	add_ask( ({"hammer", "for hammer"}), VBFC_ME("give_hammer"),1);
	set_default_answer("Aron says: ICannotHelpYouWithThat,MyFriend.\n");

	trig_new("%s 'gives' %s", "gimme");

	set_alignment(200);
	set_knight_prestige(-1);

	seteuid(getuid(TO));
	set_all_attack_unarmed(20, 20);
	set_skill(SS_DEFENSE, 50);
	set_all_hitloc_unarmed(40);
}


void
look_inv()
{
	write("Aron leans over the counter and has a look at your inventory.\n");
	say("Aron leans over the counter and has a look at " + QTNAME(TP)
		 + "'s inventory carefully.\n");
}

string
sign_check()
{
	string him;
	
	him = implode(explode(TP->query_nonmet_name(), " "), "");
	
	if (present("Gnomish_Sign", TP))
	{
		look_inv();
		command("say YouShouldReadTheLabel," + him);
         return "";
	}
	if (present("Gnomish_Incomsign", TP))
	{
		look_inv();
		command("say GiveTheSignToMe," + him 
			+ ".IWillHaveALookAtIt.");
      return "";
	}
	if ((present("nail_for_sign", TP)) && (present("stick_for_sign", TP))
		&& (present("board_for_sign", TP)))
	{
		look_inv();
		command("say Well,WhyDon'tYouTryToConstructTheSignNow,"
			+ him + "?");
		command("smile cheerfully");
      return "";
	}
	if ((present("nail_for_sign", TP)) || (present("stick_for_sign", TP))
		|| (present("board_for_sign", TP)))
	{
		look_inv();
		command("say YouDon'tSeemToHaveAllOfTheNecessary"
			+ "PartsYet," + him + ".");
      return "";
	}
	command("say ToProveYourWorthynessOfBecomingAnInventor,");
	command("say GetThePartsAndBuildASign," + him + ".");
   return "";
}


void
gimme(string str1, string str2)
{
	string *phrase;
	object ob, *inv;

	phrase = explode(str2, " ");
	if(phrase[0] != "you")
		return;
	if (ob = P("Gnomish_Incomsign", TO))
	{
		ob->remove_object();
		command("say Yes,WithThisSignSomethingIsMissing.");
		tell_room(E(TO), BSN(
		  "Aron gets a blank label from a pile, inscribes "
		+ "something onto it and affixes it to the pole of the "
		+ "sign."));
                
		TP->catch_msg("Aron gives you a gnomish sign.\n");
		tell_room(E(TO), "Aron gives a gnomish sign to "
			+ QTNAME(TP) + ".\n", TP);

		object sign = clone_object(OBJ + "sign.c");
                
                if (sign->move(P(lower_case(str1), E(TO)))) {
                    sign->move(E(TO), 1);
                    TP->catch_msg("You can't carry the sign and drop it instead.\n");
                }



		command("smile at " + lower_case(str1));
		command("say IHopeICouldHelpYou.");
		return;
	}
	else
	{
	    command("say ThankYou!");
	    inv = all_inventory();
      command("emote stores the " + inv[0]->short() 
		          + " in a shelf.");
	    inv[0]->remove_object();
	    if (inv[0]->short() == "gnomish hammer")
	    {
		         hammer_flag = 0;
		         command("say IHope,YouCompletedYourWorkToYourSatisfaction.");
		         command("smile at " + lower_case(str1));
		         return;
	     }
	     command("say IWillStoreItHereWithAllTheOtherThings.");
	     command("shrug");
	     return;
	}
}

string
give_hammer()
{
	object ob;

	if((P("lian", TP)) && (!P("nail_for_sign", TP)) && (!P("hammer", TP)))
	{
		if(hammer_flag)
		{
			command("say IAmSorry,ITemporarilyRanOutOfHammers.");
      return "";
		}
		command("say OhYes,IThinkYou'llNeedAToolForThat.");
		command("emote gets something from a shelf.");
		ob = clone_object(OBJ + "hammer.c");
		ob->set_long("A standard hammer for use when making or "
		+ "repairing things. Pretty hefty.\nA label has been "
		+ "stamped on it.\nYou borrowed it from Aron, the "
		+ "toolmaster. Return it to Aron as soon as possible.\n");
		ob->add_prop(OBJ_M_NO_SELL, "You should return it to Aron!\n");
		ob->move(E(TO));
		command("emote puts a hammer onto the counter.");
		command("say HereYouAre.I'llLendThisHammerToYou.");
		command("smile");
		hammer_flag = 1;
      return "";
	}
	command("say ForWhatShouldYouNeedOne?");
   return "";
}

void
reset_monster()	{hammer_flag = 0;}

/* Mask do_die to get the haunting */
void 
do_die(object killer)
{
  object ghost;

  seteuid(getuid());
  ghost = clone_object(TDIR + "monster/ghost"); 
  ghost->set_ghost_des(this_object()->query_nonmet_name());
  ghost->set_duration(800);
  ghost->move(killer);
  ghost->start_haunt();
  ghost->set_inform_msg("YouDeprivedMeOfThePossibilityTo"
	+ "FulfillMyTaskInTheGuild.\nYouWillSurelyPay.\n");
  ::do_die(killer);

}

