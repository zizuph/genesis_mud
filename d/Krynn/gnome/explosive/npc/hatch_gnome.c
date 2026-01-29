/**
* Coded by Louie 2004
* 
* A gnome who guards the hatch at the explosive center.  He doesn't let
* people pass if they don't have a waiver.  He'll also give them some
* help if they ask for it.
*/
#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GNOME_BASE;
inherit "/d/Krynn/std/act/gift.c";

/*prototypes*/

string no_answer();
string quest_hint();
void quest_hint2();
void give_it_back(object ob, object from);

/*variables*/
int helping;

/*
*Create
*/
void
create_krynn_monster()
{	
	if (!IS_CLONE)
	{
		return;
	}
	::create_krynn_monster();
		
    SHORT("old one-eyed gnome");
    set_name("gnome");
    add_name("_hatch_gnome");
    set_adj("old");
    add_adj("one-eyed");
    
    LONG("This old gnome works in the Hatch Room " +
    	"at the Explosives Development Center of Gnomish "+
      "Industries.  " +
      "His job is to seal the hatch when someone descends into "+
      "the Arming Room to assemble their explosive device.  " +
      "He has apparently been around for a long time, and may be "+
      "a good person to ask for advice before going down.  " +
      "\n");
    
    helping = 0;
    
    /*placehold for krynn gift*/
    add_gift("_nothing_for_you",give_it_back);
    
    add_act("emote dives behind the blast shield.");
    
    set_default_answer(VBFC_ME("no_answer")); 
        
    add_ask(({ " [about] 'help' / 'advice' / 'quest' "}),
     	VBFC_ME("quest_hint"));
     	
}


/* 
*Default answer
*/
string
no_answer()
{
	if (!CAN_SEE(TO, TP))
	{
		command("peer");
		command("say I'mSorryICan'tSeeWhoIsTalking,I'veOnlyGotOneEye"+
			"YouKnow...");
		return "";
	}
	
	command("hmm");
	command("say Sorry,IDon'tKnowAnythingAboutThat.");
	return "";
}

/*
*Respond when asked
*/
string
quest_hint()
{
	if (!CAN_SEE(TO, TP))
	{
		command("peer");
		command("say I'mSorryICan'tSeeWhoIsTalking,I'veOnlyGotOneEye"+
			"YouKnow...");
		return "";
	}
	
	command("say YourBestChanceOfSucceedingWithArmingAnExplosiveDeviceIs"+
		"IfYou'veWorkedWithTheGnomeExplosivesDesignerAndTheApprovalCommittee"+
		"AndEndedUpWithAnApprovedRequestFormAndAnApprovedDesignForm.");
	helping = 1;
	
	set_alarm(2.5,0.0,"quest_hint2");
	
	return "";
}

/*
* To increase the chance of success and get some bonus xp, the player 
* should have gotten everything approved by the actual gnomes.
*/
void
quest_hint2()
{
	object ob1, ob2, ob3;
	string str = "";
	
	command("say LetMeHaveALook...");
	
	/*Check if there is a design form and if it is approved*/
	if (!(ob1 = present("_gnome_design_form",TP)))
	{
		
		str += "YouDon'tHaveADesignFormThat'sVeryRiskyYouCanGetOneNorth"+
			"OfTheMainDesk";
		
	} 
	else if (!ob1->is_approved())
	{
		
		str += "YouProbablyWantToHaveYourDesignFormApprovedBy"+
			"TheApprovalCommitteeOnTheEastSideOfTheCenter";
	}
	
	/*Check if there is a request form and if it is approved*/
	if (!(ob2 = present("_gnome_request_form",TP)))
	{
		
		if (strlen(str))
		{
		
			str += "And";
		}
		
		
		str += "YouDon'tHaveAWaiver...IMeanRequestForm,You'llNeedTo"+
			"GetOneFromTheMainDesk";
	} else if (!ob2->is_approved())
	{
		
		str += "YouNeedToHaveYourWaiver...IMeanRequestFormApproved";
	}
	
	if (!present("_gnome_prototype", TP))
	{
		if (strlen(str))
		{
			str += "And";
		}
		
		str += "YouDon'tSeemToHaveYourPrototypeDeviceYouCanBuildOne"+
			"InTheManufacturingRoom";
	}
	
	/*If the error string is empty then we must have everything we need*/
	if (!strlen(str))
	{
	
		str = "ItLooksToMeLikeYouHaveAnApprovedDesignFormAndAnApproved"+
			"Waiver...IMeanRequestFormSoYouShouldBeGoodAssumingThat"+
			"TheFormsWereActuallyApprovedByTheGnomesAndNotSomeOtherWay";
	}
	
	str += ".";
	
	command("say "+ str);
		
	
	helping = 0;
	
}

/*
* This is to start /d/Krynn/std/act/gift.c
*/
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    recieve_gift(ob, from);
    
}

/**
* This is for krynn/std/act/gift.c
*/
public varargs void
drop_unknown(object gift, object from)
{
	command("say IDon'tNeedAnything.");
	give_it_back(gift, from);
	
}

void
give_it_back(object ob, object from)
{
    string what,
    who;

    what = L(ob->query_short());
    who = from->query_real_name();
   
   	//command("say what is *"+what+"* and who is *"+who+"*.");
    command("give " + what + " to " + who);
    
    //In case we lost our target
    command("drop " + OB_NAME(ob));
}