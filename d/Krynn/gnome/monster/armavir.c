/* created by Dajala 
 * Armavir, the Master Inventor.
 * Gives the gnomes' entrance quest.
 * (Standard-Gnome made by Grrrr).
 */

/**
 * Navarre December 27th 2007:
 * Changed the int brain method to string brain, and changed "@@brain" to brain which
 * is the preferred VBFC way.
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>   /* This is needed to be able to use the macros, IS_CLONE */
#include <ss_types.h>
#include "/d/Krynn/gnome/guild/guild.h"	/* needed for bits */

#define QUESTLOG "/d/Krynn/common/log/quests/gnome_guild"

inherit M_FILE

// Prototypes
string brain();

int no_intro;


void
create_krynn_monster()
{
    int i;

    set_name("armavir");
    add_name("emong");
    set_living_name("armavir");
    set_adj("white-haired");
    add_adj("clever");
    set_long(BSN(
	"The white-haired gnome watches you with lively, intelligent eyes. "
	+ "Then, the next moment, he seems to be completely absent, looking "
	+ "through you as if you weren't present. His fingers move "
	+ "about constantly, building something you cannot see."));
    set_race_name("gnome");
    set_title("the Master Inventor");
    if (!IS_CLONE) /* Added by Nick, to get rid of some possible errors. */
    	return;

    set_gender(0);
    set_act_time(10);
    add_act(brain);
    add_cact("say HeyHaveYouLostYourMind?");
    add_cact("say WhereWasThatFlameThrower?");

    set_cact_time(10);
    for (i = 0; i < 6; i++)
	set_base_stat(i, 50 + random(25));
    set_base_stat(1, 100);
    set_hp(15000);
    set_alignment(200);
    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(40,40);
    set_skill(SS_DEFENSE, 50);
    set_knight_prestige(-2);

    trig_new("%s 'introduces' %s","introduce_me");

    add_ask( ({"join","joining"}), "say To be able to join the guild, " +
	    "maybe you can help me first?",1);
    add_ask( ({"quest"}),"say Well, I don't have a quest for you, but I " +
	    "could need your assistance.",1);
    add_ask( ({"task" ,"help" ,"assistance","assist"}),
	    VBFC_ME("give_task"),1);
    add_ask( ({"reward", "for reward"}), VBFC_ME("reward_me"),1);

    set_alarm(1.0, -1.0, "equipme");
}

string
brain()
{
    int i;
    string *stuff;

    stuff = ({"a hammer", "a spring-loaded whatsit",
    	"several large balls of string", "a smoking pair of shoes"});
    i = random(5);
    if (i == 1)
    {
    	command("say IHaveToThinkThatOverVeryCarefully.");
    	command("think something");
    }
    else if (i == 2)
    {
    	command("say NeedsMoreBellsAndWhistlesAndStuff.");
    }
    else if (i == 3)
    {
    	command("say ThisIsAReallyImportantPartOfTheWhole.");
    	command("hmm");
    }
    else if (i == 4)
    {
	command("say INeedAVolunteerToDoATaskForMe.");
    	command("emote looks at you.");
    }
    else
    {
	tell_room(environment(), "A gnome runs by carrying " +
	    stuff[random(sizeof(stuff))] + ".\n");
    }
    return "";
}
/******************** new code *********************************/
void
introduce_me()
{
    if (no_intro)
      return;
    no_intro = 1;
    set_alarm(3.0,0.0,"intro_me");
}

void
intro_me()
{
    command("introduce me");
    no_intro = 0;
}

string
give_task()
{
    command("say InTheTestAreaForTheNewLargeMachineAHoleHas");
    command("say BeenCreatedDueToVibration.SomeGnomesWhoHad");
    command("say ALookIntoThereNeverReturned.I'dAskYouToPlant");
    command("say AWarningSignNorthOfTheGuardroomOverThere.OntoThe");
    command("say SignYouShouldWrite:'Danger!KeepOut!'.PleaseUse");
    command("say ExactlyTheseWordsSinceIWantToAvoidConfusion.");
    command("say ComeBackToMeAfterwardsAndAskForTheReward.");
    command("whisper " + lower_case(TP->query_name(TP)) + " TalkToAron,"
	+ "TheToolmaster,ForFurtherInstructions.");
   return "dummy";
}

string
reward_me()
{
    string text, who;

    who =  lower_case(TP->query_name(TP));
    text = ("/d/Krynn/gnome/caves/cav1.c"->check_for_sign());
    if((text == "Danger!KeepOut!\nSigned: " + (TP->query_name())) ||
	(text == "Danger! Keep out!\nSigned: " + (TP->query_name())) ||
	(text == "Danger! Keep Out!\nSigned: " + (TP->query_name())))
    {
	if(TP->test_bit("Krynn", GGUILD_GROUP, GQUEST_BIT))
	{
	    command("say WellDoneMyFriendAndThankYou.");
	    command("say ButYouHaveAlreadyReceivedYourReward.");
       return "dummy";
	}
	command("say ThankYou,MyFriend.");
	command("smile " + who);
	TP->set_bit(GGUILD_GROUP, GQUEST_BIT);
	TP->catch_msg("You feel more experienced.\n");
	TP->add_exp(1500, 0);
	write_file(QUESTLOG, extract(ctime(time()), 4, 15) + " "
	     + TP->query_real_name() + ".\n");
	/* We will go ahead and only let true gnomes know that they */
	/* May join this race guild (non "gnome" gnomes won't be */
	/* able to join as they must already be in a race guild */
	if((TP->query_race_name()) == "gnome")
	    command("say FurthermoreYouHaveProvenYourselfBeingWorthy");
	    command("say OfJoiningTheInventorGuild.");
	    command("congratulate " + who);
   return "dummy";
    }
    command("say ForWhatShouldIRewardYou!");
    command("say YouShouldDoWhatIAskedForFirst.");
    command("scowl " + who);
   return "dummy";
}

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
	+ "FulfillMyOfficeInTheGuild.\nYouWillSurelyPay.\n");
  ::do_die(killer);

}
