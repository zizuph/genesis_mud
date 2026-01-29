/**
* Coded by Louie 2004
* 
* A guard who stands around and assists his teammates and provides a little
* bit of info if asked.
*
*/
#pragma strict_types

#include "../local.h"
#include <macros.h>
#include <ss_types.h>

inherit GNOME_BASE;
inherit "/d/Krynn/open/auto_teaming";

/*prototypes*/

string no_answer();
string quest_hint();

void
create_krynn_monster()
{	
	string *short1;
	string *short2;
	string s1, s2;
	int i;
	
	if (!IS_CLONE)
	{
		return;
	}
	::create_krynn_monster();
		
	short1 = ({"large","burly","angry","tense","unhappy","moody"});
	short2 = ({"paranoid","careful","pensive","powerful","friendly"});
	
	s1 = short1[random(sizeof(short1))];
	s2 = short2[random(sizeof(short2))];
	
    SHORT(s1 + " " + s2 + " gnome");
    set_name("gnome");
    add_name(({"guard","_gnome_guard"}));
    set_adj(({ s1, s2, "guard" }));
    
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    
    /*help out a friend*/
    set_pick_up_team("_gnome_guard");
    set_max_team_size_auto_join(5);
    
    /*Beef them up a little bit*/
    for (i = 0; i < 6; i++)
		set_base_stat(i, 45 + random(25));
		
    set_skill(SS_DEFENSE, 50);
	set_skill(SS_WEP_CLUB, 65);
	set_skill(SS_BLIND_COMBAT, 65);
	set_skill(SS_UNARM_COMBAT, 65);
	set_skill(SS_2H_COMBAT, 55);

	if (!present("hammer",TO))
	{
    	clone_object(OLD_GNOME_OBJ+"hammer")->move(TO);
    }
    
    if (!present("helmet",TO))
    {
		clone_object(OLD_GNOME_OBJ+"helmet")->move(TO);
	}

	command("wear all");
	command("wield hammer");

    LONG("This gnome works as a guard " +
    	"at the Explosives Development Center of Gnomish "+
      "Industries.  " +
      "His time is spent keeping an eye on things, and providing " +
      "help as needed.  " +
      "\n");
    
    set_default_answer(VBFC_ME("no_answer")); 
        
    add_ask(({ " [about] 'help' / 'quest' / 'work' / " +
     	"'helping' / 'design' / 'parts' "}),
     	VBFC_ME("quest_hint"));
     	
    
     	
}

void
init_living()
{
	::init_living();
	init_team_pickup();
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
	
		
	command("say IfYouHaveAllTheApprovedPaperworkYouCanGoToThe"+
		"ManufacturingRoomToTheNorth.  IfYouNeedARequestForm,Or"+
		"ADesignForm,OrApproval,OrParts,You'llHaveToVisitTheEast"+
		"SideOfTheCenter.");
		
	return "";
}

