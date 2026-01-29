/**
* Coded by Louie 2004
* 
* A gnome who can approve designs if he is in the committee room of
* the explosive center of gnomish industries.
*
*/
#pragma strict_types

#include "../local.h"
#include <macros.h>

inherit GNOME_BASE;
inherit "/d/Krynn/std/act/gift.c";

#define IS_BUSY "/d/Krynn/gnome/explosive/room/explosive_control"->query_committee_approving()
#define SET_APPROVING(x) "/d/Krynn/gnome/explosive/room/explosive_control"->set_committee_approving(x)

/*prototypes*/

string no_answer();
string quest_hint();
void give_it_back(object ob, object from);
int handle_request_form(object ob, object from);
void begin_approval(object ob, object from, object *gnomes);
int handle_design_form(object ob, object from);
void handle_design_form2(object ob, object from);
void make_gnome_act(object gnome, string todo);

int helping;

/*
* Create
*/
void
create_krynn_monster()
{	
	
    string *short1;
    string *short2;
    string s1, s2;
    
    if (!IS_CLONE)
    {
        return;
    }
    ::create_krynn_monster();
    
    short1 = ({"small","tall","skinny","fat","pudgy","good-looking",
               "ugly","humble","haughty","happy","angry"});
    short2 = ({"quiet","loud","obnoxious","polite","smiling","intense",
               "black-haired","blond-haired","bald","thoughtful"});
    
    s1 = short1[random(sizeof(short1))];
    s2 = short2[random(sizeof(short2))];
    
    /** For krynn/std/act/gift.c**/
    add_gift("_gnome_design_form",handle_design_form);
    add_gift("_gnome_request_form",handle_request_form);
	
    SHORT(s1 + " " + s2 + " gnome");
    set_name("gnome");
    add_name("_gnome_explosive_design_approver");
    set_adj(s1);
    add_adj(s2);

    add_prop(NPC_I_NO_LOOKS, 1);

    helping = 0;
    
    set_act_time(15);
    add_act("emote tries to think of how to best add more alarms.");
    add_act("shout IsThereAMotionOnTheFloor?");
    add_act("shout OrderOrderOrder!");
    add_act("shout You,Sir,AreAnIdiot!");
    add_act("shout IWouldExpectASuggestionLikeThatFromAKender!");
    add_act("shout TheOnlyThingExplodingAroundHereIsTheSizeOfYourBottom!");
    add_act("say Isn'tThereABetterWayToDoThat?");
    
    LONG("This " + s1 + " gnome is a member of the " +
    	"Approval Committee at the Explosives Development " +
    	"Center of Gnomish Industries.  " +
      	"If you have a design you want approved, you can give it "+
      	"to him to have the committe consider it.  " +
      	"\n");
     
     set_default_answer(VBFC_ME("no_answer")); 
        
     add_ask(({ " [about] 'design' / 'my design' / 'designs' / "+
     	"'quest' / 'help' "}),
     	VBFC_ME("quest_hint"));
     	
     add_ask(
     ({" [about] 'the committee' / 'committee' / 'Committee' / "+
     	"'the Committee' "}),
     	VBFC_ME("committee_hint"));
    
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
    
    command("say ICanOnlyHelpYouWithYourDesignOrTellYouAboutTheCommittee.");
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
    
    command("say TheCommitteeIsInSession,IfYouHaveADesignYouWant"+
            "ApprovedFeelFreeToGiveItToACommitteeMember.");
    
    return "";
}

string
committee_hint()
{
    if (!CAN_SEE(TO, TP))
    {
        command("peer");
        command("say ICouldHaveSworeIHeardSomeoneSaySomething,But"+
                "IDon'tSeeWho...");
        return "";
    }
    
    
    command("say TheDesignApprovalCommitteeWillDetermineIfYourDesign"+
            "IsWorthApprovingAndIfItIsThey'llStampItWithTheSealOfApproval"+
            "AllYouHaveToDoIsGiveACommitteeMemberYourDesignAndThey'llHandle"+
            "ItFromThere!");
    
    return "";
}

/*
* If we give an approval gnome something, he'll check it out.
* If it's a design, he'll start a motion on the floor to debate and/or
* approve the design.
* Basically for a design to be approved it has to have one of everything.
*/
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    recieve_gift(ob, from);
    
    /**
    if (helping) {
    	command("say SorryI'mCurrentlyHelpingSomeoneElse.");
    	set_alarm(0.5, 0.0, &give_it_back(ob, from));
    	return;
    }

    if(ob->id("_gnome_request_form"))
    {
    helping = 1;
	set_alarm(1.0, 0.0, &handle_request_form(ob, from));
	return;
    }

    if(ob->id("_gnome_design_form"))
    {
    helping = 1;
	set_alarm(1.0, 0.0, &handle_design_form(ob, from));
	return;
    }

    command("say IDon'tKnowWhatToDoWithThis.");
    set_alarm(0.5, 0.0, &give_it_back(ob, from));
    return;
    **/
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
    string what, who;

    what = L(ob->query_short());
    who = from->query_real_name();
   
    //command("say what is *"+what+"* and who is *"+who+"*.");
    //command("give " + what + " to " + who);
    
    command("give " + OB_NAME(ob) + " to " + who);
    
    //*In case we lost our target
    command("drop "+ OB_NAME(ob));
}

/*
* Committee members don't need the request form (waiver)
*/
int
handle_request_form(object ob, object from)
{
    if (helping)
    {
    	command("say SorryI'mCurrentlyHelpingSomeoneElse.");
    	set_alarm(0.5, 0.0, &give_it_back(ob, from));
    	return 1;
    }
    
    helping = 1;
    command("say ThisIsARequestForm,NotADesignForm.  TheRequestFormIs"+
            "UsedToGetADesignFormFromTheDesigningRoomNorthOfTheMainDesk.");
    set_alarm(0.5, 0.0, &give_it_back(ob, from));
    helping = 0;
    return 1;
}


/*
* Start checking out the design form.  
*/
int
handle_design_form(object ob, object from)
{
    if (helping)
    {
    	command("say SorryI'mCurrentlyHelpingSomeoneElse.");
    	set_alarm(0.5, 0.0, &give_it_back(ob, from));
    	return 1;
    }
    
    helping = 1;
    
    if (ob->is_approved())
    {
        command("say ThisDesignFormIsApprovedSoTheNextStepWouldBeTo"+
                "TakeItToTheShopSouthOfTheMainDeskAndGetYourPartsForAssembling"+
                "YourDevice.");
        set_alarm(0.5, 0.0, &give_it_back(ob, from));
        helping = 0;
        return 1;
    }
	
    if (!(environment(TO)) ||
        !(environment(TO)->query_short() == 
          "Approval Room in the Explosives Development Center"))
    {
        command("say SorryButI'mNotWorkingRightNow,MaybeYouShouldGo"+
                "ToTheApprovalCommitteeRoomAndSeeIfSomeoneIsThere.");
        set_alarm(0.5, 0.0, &give_it_back(ob, from));
        helping = 0;
        return 1;
    }

    if (IS_BUSY)
    {
        command("say TheCommitteeIsCurrentlyConsideringAnotherDesign,"+
                "PleaseWaitUntilWe'reFinishedBeforeGivingUsYourDesign.");
        set_alarm(0.5, 0.0, &give_it_back(ob, from));
        helping = 0;
        return 1;
    }
    command("say OhIsThisYourDesign?  I'llPresentItToTheCommitteeImmediately!");
    SET_APPROVING(1);
		
    set_alarm(2.5,0.0, &handle_design_form2(ob, from));
    
    return 1;
}

/*
* The design actually starts being debated by all the gnomes in the room.
*/
void
handle_design_form2(object ob, object from)
{
    string what, who, phrase;
    object *gnomes;
    object *everything;
    int g = 0;
    int i = 0;
		
    who = from->query_name();
	
    if (ob->component_ct() < 1)
    {
        command("say WaitAMinute!  ThisDesignDoesn'tHaveAnyComponentsStopWastingOurTime.");
        set_alarm(0.5, 0.0, &give_it_back(ob, from));
        SET_APPROVING(0);
        helping = 0;
        return;
    }
	
    everything = all_inventory(environment(TO));
    
    for (i = 0; i < sizeof(everything); i++)
    {
        
        if (!(everything[i]->id("_gnome_explosive_design_approver")))
        {
            everything[i] = 0;
            g--;
        }
        
        g++;
    }
    
    gnomes = allocate(g);
    g = 0;
    
    for (i = 0; i < sizeof(everything); i++)
    {
        if (everything[i])
        {
            gnomes[g] = everything[i];
            g++;
        }
    }
    command("shout AttentionEveryoneIHaveADesignToApprove!");
    
    set_alarm(2.5, 0.0, &begin_approval(ob, from, gnomes));
}

/*
* Just check the design form for components, and comment on each one.
* At the end of the method they either get their design approved or not.
*/
void
begin_approval(object ob, object from, object *gnomes)
{
    string *badbegins = ({"HaHaHaHaHa!  ",
                          "That'sTheStupidestThingI'veEverSeen!  ",
                          "You'veGotToBeKiddingMe!  ",
                          "IsThisSomeKindOfJoke?  ",
                          "AreTheySerious?  "});
    
    string *randombegins = ({"HmmI'veNeverThoughtOfThat...  ",
                             "That'sADifferentApproach, ",
                             "OfCourseWhatAGoodIdea!  " });
    
    string *randombegins2 = ({
        "It'sSoCrazyItJustMightWork!  ",
        "IHaveMyDoubts,ButWhoKnowsMaybeIt'llActuallyExplode.  ",
        "WhoCaresIfItWillWork, It'sNotLikeIt'sMyAssThat'sGoingToGetBlownOff.  ",
      	"I'mHungryCanWeHurryThisUp?  "});		
		
    string *phrase = allocate(10);
    string *randompieces = allocate(50);
    int p = 0;
    int r = 0;
    int i = 0;
    float timebetween = 4.0;
    
    tell_room(environment(TO), "The gnomes gather around " +
              "the design, studying it closely.\n", 0, environment(TO));
	
    /*We require at least one of each type*/
    if (ob->total_eff_ct() < 1)
    {
        phrase[p] = "ThisDesignDoesn'tHaveAnyEffects!";
        p++;
    } 		
    
    if (ob->total_damage_ct() < 1)
    {
        phrase[p] = "WhatIsGoingToActuallyCauseTheDamage?";
        p++;
    }
    
    if (ob->total_alarm_ct() < 1)
    {
        phrase[p] = "ObviouslyThisNeedsMoreBellsAndWhistlesAndStuff!";
        p++;
    }
    
    if (ob->total_delay_ct() < 1)
    {
        phrase[p] = "ThereShouldBeAtLeastSomeSortOfDelayingAgent!";
        p++;
    }
	
    if (ob->total_ignit_ct() < 1)
    {
        phrase[p] = "HowDoTheyExpectTheDeviceToIgnite?";
        p++;
    }
	
    if (ob->total_combus_ct() < 1)
    {
        phrase[p] = "ThereAreNoCombustionParts!";
        p++;
    }

    /*Build the list of existing components*/
    if (ob->eff_damage_ct())
    {
        randompieces[r] = "ADamagingComponent";
        r++;
    }
    
    if (ob->eff_disarm_ct())
    {
        randompieces[r] = "ADisarmingComponent";
        r++;
    }
    
    if (ob->alarm_bell_ct())
    {
        randompieces[r] = "ABell";
        r++;
    }
    
    if (ob->alarm_whistle_ct())
    {
        randompieces[r] = "AWhistle";
        r++;
    }
    
    if (ob->damage_shrapnel_ct())
    {
        randompieces[r] = "TheShrapnelDamage";
        r++;
    }
    
    if (ob->damage_chemical_ct())
    {
        randompieces[r] = "TheChemicalDamage";
        r++;
    }
    
    if (ob->combus_chemical_ct())
    {
        randompieces[r] = "TheChemicalCombustion";
        r++;
    }
    
    if (ob->combus_mineral_ct())
    {
        randompieces[r] = "TheMineralCombustion";
        r++;
    }
    
    if (ob->delay_fuse_ct())
    {
        randompieces[r] = "AFuse";
        r++;
    }
    
    if (ob->delay_timer_ct())
    {
        randompieces[r] = "ATimer";
        r++;
    }
    
    if (ob->ignit_flint_ct())
    {
        randompieces[r] = "AFlintIgnition";
        r++;
    }
    
    if (ob->ignit_steam_ct())
    {
        randompieces[r] = "ASteamIgnition";
        r++;
    }
    
    /*figure out how many entries we really have*/
    r = 0;
    
    for (i = 0; i < sizeof(randompieces); i++)
    {
        if (randompieces[i])
        {
            r++;
        }
    }
    
    if (r)
    {
        if (r > 3) 
        {		
            set_alarm(timebetween, 0.0, 
                      &make_gnome_act(
                                      gnomes[random(sizeof(gnomes))],
                                      "say "+randombegins[random(sizeof(randombegins))] +
                                      "Combining"+
                                      randompieces[random(r)] +
                                      "With"+
                                      randompieces[random(r)] +
                                      "InThatWay."));
            
            timebetween += 4.0;
            
        }
        
        set_alarm(timebetween, 0.0, 
                  &make_gnome_act(gnomes[random(sizeof(gnomes))], 
                                  "say "+randombegins2[random(sizeof(randombegins2))]));
        
        timebetween += 4.0;
        
        set_alarm(timebetween, 0.0, 
                  &make_gnome_act(gnomes[random(sizeof(gnomes))], 
                                  "say "+randombegins[random(sizeof(randombegins))] +
                                  "Attaching"+
                                  randompieces[random(r)] +
                                  "InSuchAFashion."));
        
        timebetween += 4.0;
    }
	/*figure out how many entries we really have*/
    p = 0;
    
    for (i = 0; i < sizeof(phrase); i++)
    {
        if (phrase[i])
        {
            p++;
        }
    }
    
    for (i = 0; i < p; i++)
    {
        set_alarm(timebetween, 0.0, 
                  &make_gnome_act(gnomes[random(sizeof(gnomes))],
                                  "say "+badbegins[random(sizeof(badbegins))] +
                                  phrase[i]));
        
        timebetween += 4.0;
    }	
    
    if (p)
    {
        set_alarm(timebetween, 0.0,
                  &make_gnome_act(TO,
                                  "say YouShouldReallyFixSomeOfThoseFlawsAndComeBack"+
                                  "WithYourImprovedDesign."));				
    }
    else
    {
        set_alarm(timebetween, 0.0,
                  &make_gnome_act(TO,
                                  "say Congratulations!  I'llStampYourDesignForYou"+
                                  "RightNow!"));
        
        /** Add prop to give xp bonus and chance to succeed bonus **/
        TP->add_prop(LIVE_I_DESIGN_APPROVED, 1);
        
        timebetween += 1.5;
        
        set_alarm(timebetween, 0.0,
                  &make_gnome_act(TO, "approve design"));
        
        
        timebetween += 2.0;
    }
    set_alarm(timebetween, 0.0, &give_it_back(ob, from));
    SET_APPROVING(0);
    helping = 0;
}

void
make_gnome_act(object gnome, string todo)
{
    gnome->command(todo);
}

