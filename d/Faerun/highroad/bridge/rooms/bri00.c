/*
 * The Northern end of the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

//inherit BASE_ROAD;
inherit "/d/Faerun/highroad/bridge/std/base_road.c";

static object *guard = ({0,0,0,0,0});

void
create_road()
{
    set_short("an old stone bridge");
    set_extraline("The road heads north across the stone bridge and " +
	"towards a walled city. It looks as if the road was well " +
        "travelled quite recently but it is nearly empty right now. " +
	"A barricade stands just before the bridge. Further north you can see the Neverwinter " +
	"city raising above the walls that surround it. It looks as if " +
        "it is covered with a delicate mist.\n");

    add_features(({"bridge", "barricade", "nw_city_n_far", "river",
    	"highroad", "neverwinterf", "grasslands"}));
    
    reset_faerun_room();


    add_exit(BR_DIR + "bri01", "north", "@@block_room@@");
    add_exit(HR_DIR + "nrd08", "south");

}

public void
init()
{
    ::init();
}

     


void
reset_faerun_room()
{
	int i;
	
	if (!guard[0]) {
		guard[0] = clone_object(NPC_DIR + "sergeant");
		guard[0] -> move (TO);
	}
	
	for (i=1; i<5; i++) {
		if (!guard[i]) {
			guard[i] = clone_object(NPC_DIR + "random_guard");
			guard[i] -> move (TO);
			guard[0] -> team_join(guard[i]);
		}
	}

	// EMOTES
	guard[0] -> set_act_time(50+random(50));
	guard[0] -> add_act("listen attent");
	guard[0] -> add_act("emote studies his weapons carefully");
	guard[0] -> add_act("say Noone is allowed to go to Neverwinter, at least until priests contain the plague."); 
	guard[0] -> add_act("say If you brought some aid for Neverwinter you may offload it here. Someone will surely come soon to pick it up.");
	guard[0] -> add_act("say I have heard they may soon have trouble feeding all the people. Unless the plague kills them faster.");
	
	guard[0] -> add_cact("shout In the name of Lord Asher! Back off!");
		
	string *acts = ({
		"say I wish I had a swift death. Those who have fallen to the plague suffer horribly.", 
		"emote looks worriedly towards Neverwinter", 
		"say The plague killed my brother!",
		"say I have seen infected people... Horrible sight."});
		
	string *cacts = ({
		"roar", "say You will regret this!", "say Curse on you!", "say I hope the plague gets you!"});
		



	// WARNING - sizeof(acts) MUST not be greater than 5 !
	//for (i=1; i<sizeof(acts); i++) {
	for (i=1; i<5; i++) {
		guard[i] -> set_act_time(50+random(100));
		guard[i] -> set_cact_time(50+random(100));
		guard[i] -> add_act(acts[i-1]);
		guard[i] -> add_cact(cacts[i-1]);
		// Delay first add_act
		// _mon_ran_act is taken from /std/act/action.c and is an identifier of add_act managed commands
		// second argument is a timout
		// for more info - see /std/act/seqaction.c
		
		// does it really work ?
		guard[i] -> seq_addfirst("_mon_ran_act", 10*random(20)); 
	}
}



int
block_room()
{
    int i;
    
    for(i=0; i<sizeof(guard); i++) {
    	if (guard[i]) {
    		TP->catch_vbfc(QCTNAME(guard[i]) + " stands in your way.\n");
    		tell_room(ENV(TP), QCTNAME(guard[i]) + " stands in " + QCTNAME(TP) + " way.\n", TP); 
    		guard[i]->command("say Neverwinter is under quarantine now! By order of Lord Nasher Alagondar " +
    			"noone is allowed to go there!");
    		guard[i]->command("say And if I may add... Noone sane would go there anyway.");
			
			if (TP->query_wiz_level()) {
				TP->catch_tell("Since you are a wizard you may pass anyway.\n");
				return 0;
			}
    		return 1;
    	}
    }
    return 0;
}
