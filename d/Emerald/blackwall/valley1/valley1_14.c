/* A valley in the southern Blackwall mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";
inherit BLACKWALL_VALLEY1_DIR + "pct_hurt.c"; //used when a players falls...

//prototypes:
int climb_cliff(object player);
void fall(object player, int falltime);
void get_to_ledge(object player);
int leave_room();
string ledge_descrip();

void
create_valley_room()
{
    set_short("In a rocky valley at the southern end of the Blackwall "+
	      "mountains.\n");
    
    set_em_long("In a rocky valley in the southern portion of the "+
		"Blackwall mountains. Boulders and exposed bedrock "+
		"make travelling through this valley difficult. "+
		"Few plants grow here due to a lack of soil. "+
		"It is possible to travel either east or southwest "+
		"along the valley.\n");

    add_prop(ROOM_I_HIDE, 10); //little cover

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_item(({"plants", "vegetation", "grasses", "moss", "bushes",
		   "patches", "patches of moss", "crevices"}),
	     "Some bushes have managed to find a foothold between "+
	     "the black boulders, while grasses grow wherever they "+
	     "may. Small patches of moss can be found in the darkest "+
	     "and moistest of crevices.\n");

    add_item(({"rocks", "rock", "boulders"}),
	     "The mountains are made of a coal-black basalt.\n");
   
    add_item(({"mountains", "Blackwall mountains", "Blackwall Mountains"}),
	     "You are travelling in the southernmost end of the Blackwall "+
	     "mountains, so named because they are composed chiefly of "+
	     "black rock. Jagged black cliffs mar "+
	     "the face of the tall mountain on the northern side of the "+
	     "valley while a lesser mountain lies to your south.\n");

    add_item(({"southern mountain", "south mountain", "lesser mountain"}),
	     "The mountain on the southern side of the valley is not "+
	     "of a particularly massive height. However, it would be an "+
	     "imposing climb for it consists of many jagged cliff faces, "+
	     "particularly near the top.\n");

    add_item(({"cliff", "cliffs", "northern mountain", "north mountain",
		 "tall mountain", "northern flank", "black cliffs"}),
	     "The black cliffs which make-up the northern flank of the "+
	     "valley jut skyward a hundred metres or more. There are a "+
	     "few ledges and handholds, so the cliffs could be scaled by "+
	     "an experienced climber...\n");

    add_item(({"ledge","ledges", "ledges and handholds", "handholds"}),
	      "@@ledge_descrip@@");
   
   
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_13", "southwest", leave_room, 4, 0);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_16", "east", leave_room, 4, 0);
}

/* VBFC description of the ledge. This will vary depending upon whether or not
   any livings are upon the ledge.
*/
string 
ledge_descrip()
{
    int i; //index
    object ledge; // valley1_15.c
    object *livings; //All living objects in valley1_15.
    string *descrips; //Descriptions as seen by this_player for *livings.
    string return_value;
    descrips = ({"a thick growth of bushes"});

// Make sure the room is loaded first, before assigning it to a variable:
    LOAD_ERR(BLACKWALL_VALLEY1_DIR + "valley1_15");
    ledge = find_object(BLACKWALL_VALLEY1_DIR + "valley1_15");
    livings = FILTER_LIVE(all_inventory(ledge));
   
/* Here we will get the art_name of every living in valley1_15 as
   viewed by the examining player: */

    for (i = 0; i < sizeof(livings); i++)
    {
	descrips += ({livings[i]->query_art_name(this_player())});
    }

    return_value = "There is a wide ledge some twenty-five metres up "+
	"the northern cliff face. Upon it are " + COMPOSITE_WORDS(descrips) +
	".\n";

    return return_value;
}

/* This function ensures that players do not leave this room while 
   in the middle of climbing up or down the cliff herein.
*/

int
leave_room()
{
    if (this_player()->query_prop("_climbing_bandit_cliff"))
    {
	this_player()->catch_tell("A little hasty, aren't we?\nYou sagely decide "+
				 "that you will wait until you are on the ground "+
				 "before trying to leave the valley.\n");
	return 1; // Player does not leave the room.
    }

    else
    {
	return 0; // Player leaves the room.
    }
}
/* Called when a player attempts to climb the cliff.
 */
 
int
prepare_to_climb(string str)
{    
    object player = this_player();

    // Allow for "climb to ledge", "up to ledge" and "to the ledge".

    if ((parse_command(str, ({}), "[up] 'to' [the] 'ledge'")) ||

	/* Allows for "climb up the cliff", "climb cliff",
	   "climb the cliffs" etc. 
	   An imperfect parse in that "climb up the face face" will
	   work, however thats the price we pay to allow for 
	   "climb up the cliff face" in a simplistic manner.
	*/

	(parse_command(str, ({}), "[up] [the] 'cliff' / 'face' "+
	"/ 'cliffs' [face]")))

// Command succesful:	
    {
	if (this_player()->query_prop("_climbing_bandit_cliff"))
	{
	    notify_fail("You are already climbing the cliff!\n");
	    return 0;
	}
	
	else
	{
	    write("You begin to examine the cliff face, attempting to "+
		  "find a climbable path up the black rock cliff.\n");
	    say(QCTNAME(player) + " begins a careful evaluation "+
		"of the cliff face.\n");
	    set_alarm(2.0, 0.0, &climb_cliff(player)); //looks more realistic
	    return 1;
	}
    }
    
// Syntax failure:	
    else
    {
	notify_fail("Climb what?\n");
	return 0;
    }
}

/* Called when a player climbs the cliff.
 */

void
climb_cliff(object player)
{
    int falltime, climb_ability;
    falltime = random(5); // How long before the player falls, if
                              // he fails his climbing check.

/* Make sure the player hasn't wandered off in the two seconds he was
   "looking for the best route up the cliff":
*/
    
    if (!(present(player)))
    {
	write("You have abandoned your search for a way up the cliff.\n");
	return;
    }

/* If the players skill is really low, he will not be able to find
   what he considers a safe path up the cliff:
*/

    if (player->query_skill(SS_CLIMB) < 15)
    {
	write("The cliff is clearly too difficult for you to climb.\n");
	return;
    }

    write("You find what you believe to be the easiest method of egress, "+
	  "and begin the slow, arduous task of climbing the cliff face.\n");
    say(QCTNAME(player) + "  begins the arduous task of climbing the "+
	"northern cliff face.\n");

/* The player thinks he has a chance of making it. Of course, he might 
   be mistaken - lets find out if he is:

   Chance of success is based mostly on the players climb skill, but 
   Dex does help, and being encumbered most certainly makes it harder.
*/
    climb_ability = player->query_skill(SS_CLIMB) + 
	(player->query_stat(SS_DEX) / 10) - 
	(player->query_encumberance_weight() / 2);
    
    player->add_prop("_climbing_bandit_cliff", 1);
    player->add_prop(LIVE_S_EXTRA_SHORT, " is climbing up the cliff");

    if (climb_ability + random(10) > 35)
	// requires conf.acolyte climb to guarantee success.
    {
	//The player made it:
	//It takes 5 seconds to climb the cliff:

      set_alarm(5.0, 0.0, &get_to_ledge(player));
    }
	    
    else
    {
	//The player will fall, at some random point in the climb.
	
	set_alarm(itof(falltime), 0.0, &fall(player, falltime));
    }
    return;
}

/* Called when a player succesfully climbs the cliff. Moves
   the player to valley1_15.
*/

void
get_to_ledge(object player)
{
    player->remove_prop("_climbing_bandit_cliff");
    player->remove_prop(LIVE_S_EXTRA_SHORT);
    player->add_fatigue(10); //Climbing is exhausting.
    write("You have managed to haul yourself up to the ledge.\n");
    say(QCTNAME(player) + " has managed to climb up to the "+
	"ledge.\n");  
    player->move_living("M", BLACKWALL_VALLEY1_DIR + "valley1_15", 1, 0);
    
    return;
}

/* Called when a player tries, but fails to climb the cliff
   and falls off. Deals damage to the player, and prints
   nifty messages.
*/

void
fall(object player, int falltime)
{
    int damage; //damage the player takes from the fall.
    int phurt;  //proportion of remaining hp lost in the fall

    write("You reach up for a handhold "+
	  "but to your horror pull "+
	  "a loose rock off of the cliff face!!\n" +
	  "Thrown off balance, you begin to plummet towards the "+
	  "ground!\n");

    say(QCTNAME(player) + " falls off the cliff!\n");
    player->command("$scream");

    damage = 50*(2^(5 - falltime)) + random(400);
    phurt = pct_hurt(damage, player); 
    player->heal_hp(-(damage));	    
	   
    if (player->query_hp() < 1)

    // Player has taken lethal damage:	
    {
	write("Pain wracks your body during the moment of impact, but "+
	      "then you feel nothing at all.\n");
	say(capitalize(player->query_possessive()) + " body shatters upon "+
	    "impact with the rocky ground!\n");
	player->do_die(this_object());
    }

    else   
    {
	switch(phurt)
	{

	case 0..25:
	    write("You plummet along the side of the cliff, brushing "+
		  "against it in an attempt "+
		  "to slow your fall.\n You land awkwardly "+
		  "but suffer only some scrapes and bruises.\n");
	    say(capitalize(player->query_pronoun()) + " manages to slow "+
		player->query_possessive() + " fall by brushing against "+
		"cliff face. Miraculously, " + player->query_pronoun() + 
		"only suffers fromv some cuts and bruises.\n");
	    break;

	case 26..50:

	    write("Fortuitously, you land on relativly soft ground "+
		  "and thus sustain no life-threatening injuries.\n");
	    say("Fortuitously, " + player->query_pronoun() + " lands on "+
		"relativly soft ground and sustains no life-threatening "+
		"injuries.\n");
	    break;

        default:

	    write("Pain engulfs your body as you impact with the rocky "+
		  "ground. You lose consciousness and enjoy a brief moment "+
		  "of painless ecstasy before returning to a haze of agony. "+
		  "You are very fortunate to be alive!\n");
	    say(capitalize(player->query_pronoun()) + " lands upon the rocky "+
		"valley floor with a resounding thud. You suspect the worst "+
		"until " + player->query_pronoun() + " opens " +
		player->query_possessive() + " eyes and groans.\n");	
	}    

//Clean-up:	

	player->remove_prop("_climbing_bandit_cliff");
	player->remove_prop(LIVE_S_EXTRA_SHORT);
	player->add_fatigue(falltime); //Climbing is exhausting.
	player->command("$look");
    }
    return;
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}   

void
init()
{
    ::init();
    add_action(prepare_to_climb, "climb");
}




