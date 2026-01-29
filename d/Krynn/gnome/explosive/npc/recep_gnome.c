/**
* Coded by Louie 2004
* 
* The gnome at the main desk of the gnomish explosive center.
* He gets people started on the "build a bomb" quest.
*/
#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GNOME_BASE;

/*prototypes*/

int helping;
string no_answer();
string quest_hint();
void quest_hint2();
void quest_hint3();
void quest_hint4();

void
create_krynn_monster()
{	
	if (!IS_CLONE)
	{
		return;
	}
	::create_krynn_monster();
		
    SHORT("receptionist gnome");
    set_name("gnome");
    set_adj("receptionist");
    add_name("_gnome_receptionist");
    
    LONG("This gnome works the main desk " +
    	"at the Explosives Development Center of Gnomish "+
      "Industries.  " +
      "He is probably knowledgeable about the work that goes "+
      "on here.  " +
      "\n");
     
     set_default_answer(VBFC_ME("no_answer")); 
        
     add_ask(({ " [about] 'help' / 'task' / 'work' / "+
     	"'helping' / 'quest'"}),
     	VBFC_ME("quest_hint"));
    
}

void
reset_krynn_monster()
{
	helping = 0;
}

string
no_answer()
{
	if (!CAN_SEE(TO, TP))
	{
		command("jump");
		command("say WhoSaidThat?");
		return "";
	}
	
	command("hmm");
	command("say Sorry,IDon'tKnowAnythingAboutThat.");
	return "";
}

string
quest_hint()
{
	if (!CAN_SEE(TO, TP))
	{
		command("jump");
		command("say WhoSaidThat?");
		return "";
	}
	
	if (helping) {
		command("say I'mCurrentlyTalkingToSomeoneElsePleaseBe"+
			"Patient...");
		return "";
	}
	
	helping = 1;
	
	command("smile helpf");
	command("say OhAreYouTrulyInterestedInHelpingUsOut?  That'sGreat!");
	set_alarm(3.5,0.0,"quest_hint2");
	
	return "";
}

void
quest_hint2()
{
	command("wring eager");
	command("say TheOnlyThingWeWorkOnIsDesigningAndBuilding"+
		"PrototypeExplosiveDevicesForTheKnightsBecauseTheyPay"+
		"UsQuiteWellToDevelopAnySortOfWarfareToolsAndObviously"+
		"AConsistentlySafeAndEffectivePortableExplosiveDevice"+
		"WouldBeAmazinglyUsefulToHaveOnTheBattleField!");
	set_alarm(8.5,0.0,"quest_hint3");


}

void
quest_hint3()
{

	command("sigh sadl");
	command("say UnfortunatelyThe\"ConsistentlySafeAndEffective\"Part"+
		"ContinuesToEludeMostOfOurDesigns.");
	command("shrug");
	set_alarm(4.5,0.0,"quest_hint4");

}

void
quest_hint4()
{
	command("say IfYouAreWillingToHelpDesignAndBuildAnExplosiveDevice"+
		"AllYouWouldHaveToDoToGetStartedIsSignAFormOnTheDeskThere...");
	command("point desk");
	command("say AndTakeItWithYouToTheDesignRoom...");
	command("point north");
	command("say That'sAboutAllICanTellYou.");
	command("smile helpf");
	helping = 0;

}