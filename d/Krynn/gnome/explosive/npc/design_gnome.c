/**
* Coded by Louie 2004
* 
* This gnome works in the design room (expl3) of the gnomish explosive area.
* He'll give people a design form if they give him a signed waiver which
* they can get at the main desk (expl1).  If the waiver/request form is 
* signed he'll approve it.  If this quest gives xp, this may give some
* bonus xp (having him approve it) since the player is going through
* the proper procedure.  It's also possible to just kill the gnome and
* get a design form yourself.
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
int handle_request_form(object ob, object from);
void handle_request_form2(object ob, object from);
int handle_design_form(object ob, object from);
void handle_design_form2(object ob, object from);

int helping;

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
		
    SHORT("small red-haired gnome");
    set_name("gnome");
    add_name("_gnome_designer");
    set_adj("small");
    add_adj("red-haired");
    
    LONG("This gnome works in the Design Room " +
    	"at the Explosives Development Center of Gnomish "+
      "Industries.  " +
      "He spends his time helping others get started on " +
      "their designs for explosive devices.  " +
      "\n");
     
    helping = 0;
    
    /** This is from krynn gift.c**/ 
    add_gift("_gnome_design_form",handle_design_form);
    add_gift("_gnome_request_form",handle_request_form);
    
    set_default_answer(VBFC_ME("no_answer")); 
        
    add_ask(({ " [about] 'help' / 'design' / 'work' / " +
     	"'quest' / 'helping' / 'designs' "}),
     	VBFC_ME("quest_hint"));
     	
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
	
	
	if (helping) {
		command("say I'mCurrentlyTalkingToSomeoneElsePleaseBe"+
			"Patient...");
		return "";
	}
			
	command("say Ah,WantingToDesignSomethingEh?");
	helping = 1;
	
	set_alarm(2.5,0.0,"quest_hint2");
	
	return "";
}

void
quest_hint2()
{
	
	command("say AllYouHaveToDoIsGiveMeASignedRequestFormAndThenYou"+
		"CanGetADesignFormAndGetStartedDesigning.");
	command("smile helpf");
command("say AlsoYouCanGiveMeADesignFormYouHaveWorkedOnAnd"+
    "IWillTellYouWhatIThink.");
	helping = 0;
	
}

/**
* This is for krynn/std/act/gift.c
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
	command("say IDon'tKnowWhatToDoWithThis.");
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
    
    //In case there is nobody to give it to
    command("drop " + OB_NAME(ob));
}

int
handle_request_form(object ob, object from)
{
	
	command("say OkOk,Let'sSeeWhatWeHaveHere...");
	command("emote looks over the form.");
	
	set_alarm(2.5, 0.0, &handle_request_form2(ob, from));
	return 1;
}

/*
* Check out a request form that was given to us and see if it meets
* our standards.  If it does, approve it (and maybe set a prop in the
* player for bonus quest xp?).
*/
void
handle_request_form2(object ob, object from)
{
	string what, who, whoname, signer;
	
	signer = ob->query_owner();
	who = from->query_name();
	whoname = find_player(who)->query_the_name();

	if (ob->is_approved())
	{
		command("say ThisRequestFormIsAlreadyApprovedIDon'tNeedIt"+
			"ForAnythingButIfYouWantYou'reAllowedToGetADesignFormFrom"+
			"TheBox,AssumingYouAre"
			+who+
			".");
		set_alarm(0.5, 0.0, &give_it_back(ob, from));
		helping = 0;
		return;
	}
	
	if (!(signer == who))
	{
		command("hmm");
		command("say IDon'tThinkYourSignatureIsOnHereYouShould"+
			"ReallyGoToTheMainDeskAndSignARequestFormAndBringIt"+
			"Back.");
		command("say YouCanHaveThisBack.");
		set_alarm(0.5,0.0, &give_it_back(ob, from));
		helping = 0;
		return;		
	}
	
	command("smile bright");
	command("say Yep,YouSignedAWaiver..IMeanRequestFormAllRightIGuess"+
		"YouCanGetStartedI'llJustApproveThisAndThenYouCanGetADesignForm"+
		"FromTheBoxIfYouDon'tAlreadyHaveOne.");
	command("emote approves a request form.");
	ob->approve();
	
	TP->add_prop(LIVE_I_WAIVER_APPROVED, 1);
	
	set_alarm(0.5, 0.0, &give_it_back(ob, from));
	
	helping = 0;
	
}

int
handle_design_form(object ob, object from)
{
	
	command("say AhADesignForm,IDon'tNeedThisButI'llBeHappyToTakeALookAt"+
		"It.");
	command("emote scans the design form.");
	
	set_alarm(2.5,0.0, &handle_design_form2(ob, from));
	
	return 1;
}

/*
* Give some info about a design form that was given to us, just to be
* helpful.
*/
void
handle_design_form2(object ob, object from)
{
	string what, who, signer, phrase;
	
	signer = ob->query_owner();
	who = from->query_name();

	if (ob->is_approved())
	{
		command("say ThisDesignFormFormIsApprovedSoTheNextStepWouldBeTo"+
			"TakeItToTheShopSouthOfTheMainDeskAndGetYourPartsForAssembling"+
			"YourDevice.");
		set_alarm(0.5, 0.0, &give_it_back(ob, from));
		helping = 0;
		return;
	}
	
	if (ob->component_ct() < 1)
	{
		command("say ThisDesignDoesn'tHaveAnyComponents,YouShouldTry"+
			"ToAddComponents.");
		set_alarm(0.5, 0.0, &give_it_back(ob, from));
		helping = 0;
		return;
	}
	
	if (ob->component_ct() < 6)
	{
		command("say I'mNotSureYourDesignHasEnoughComponentsToPlease"+
			"TheApprovalCommittee,ButWhoKnows?");
		command("say You'llJustHaveToTakeItToThemToFindOutForSure - "+
			"They'reNorthAndEastOfTheMainDesk.");
		set_alarm(1.0, 0.0, &give_it_back(ob, from));
		helping = 0;
		return;
	}
	
	command("say Well,IDon'tSeeAnyGlaringErrorsInTheDesignButI'm"+
		"NotReallyAGoodJudgeOfDesigns,IOnlyGotThisJobBecauseI'mUnion.");
	command("say You'llHaveToTakeItToTheApprovalCommitteeToSeeIfThey"+
		"LikeYourDesign - They'reNorthAndEastOfTheMainDesk.");
		set_alarm(1.0, 0.0, &give_it_back(ob, from));
	helping = 0;
}
