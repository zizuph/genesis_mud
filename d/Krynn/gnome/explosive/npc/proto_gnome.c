/**
* Coded by Louie 2004
* 
* A gnome works in the Manufacturing room.  He provides some help if asked.
*
*/
#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GNOME_BASE;

/*prototypes*/

string no_answer();
string quest_hint();
string quest_hint2();
string quest_hint3();
string quest_hint4();
string quest_hint5();

/*
* Create
*/
void
create_krynn_monster()
{	
	if (!IS_CLONE)
	{
		return;
	}
	::create_krynn_monster();
		
    SHORT("nervous blue-eyed gnome");
    set_name("gnome");
    add_name("_gnome_proto");
    set_adj("nervous");
    add_adj("blue-eyed");
    
    LONG("This gnome works in the Manufacturing Room " +
    	"at the Explosives Development Center of Gnomish "+
      "Industries.  " +
      "He is responsible for making sure that everyone who attempts "+
      "to build a prototype explosive device has the proper paperwork.  " +
      "\n");
     
    
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    
    set_default_answer(VBFC_ME("no_answer")); 
        
    add_ask(({ " [about] 'help' / 'work' / " +
     	"'quest' / 'helping' / 'designs' "}),
     	VBFC_ME("quest_hint"));
     	
    add_ask(({ " [about] 'request' / 'request form' / "+
    	"'waiver' "}),
    	VBFC_ME("quest_hint2"));
    	
   	add_ask(({ " [about] 'design' / 'design form' "}),
   		VBFC_ME("quest_hint3"));
   		
   	add_ask(({ " [about] 'parts' / 'parts box' / "+
   		"'box of parts' "}),
   		VBFC_ME("quest_hint4"));
   		
   	add_ask(({ " [about] 'form' / 'forms' / 'paper' "+
   		"'papers' / 'paperwork' / 'proper papers' "}),
   		VBFC_ME("quest_hint5"));
    
     	
}


string
no_answer()
{
	if (!CAN_SEE(TO, TP))
	{
		command("peer");
		command("say ICouldHaveSworeIHeardSomeoneSaySomething,But"+
			"IDon'tSeeWho...");
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
		command("peer");
		command("say ICouldHaveSworeIHeardSomeoneSaySomething,But"+
			"IDon'tSeeWho...");
		return "";
	}
	
	/*
	if (helping) {
		command("say I'mCurrentlyTalkingToSomeoneElsePleaseBe"+
			"Patient...");
		return "";
	}
	*/
			
	command("say IfYouWantToAttemptToConstructYourPrototypeGoAheadAsLong"+
		"AsYouHaveYourRequestFormAndDesignAndParts.");
	
	return "";
}

string
quest_hint2()
{
	
	command("say YouGetARequestFormFromTheMainOfficeAtTheEntranceToThe"+
		"ExplosivesCenter.");
	command("smile helpf");
	return "";
	
}

string
quest_hint3()
{
	
	command("say YouGetADesignFormNorthOfTheMainOffice.");
	command("smile helpf");
	return "";
	
}

string
quest_hint4()
{
	
	command("say YouGetABoxOfPartsFromTheShopSouthOfTheMainOffice.");
	command("smile helpf");
	return "";
	
}

string
quest_hint5()
{
	
	command("say YouGetYourPaperworkFromTheGnomesAroundHereStartingAtThe"+
		"MainOffice.  "+
		"You"+
		"NeedARequestForm,ADesign,AndABoxOfParts.");
	command("smile helpf");
	return "";
	
}
