/* A valley in the southern Blackwall mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";
inherit BLACKWALL_VALLEY1_DIR + "pct_hurt.c"; //used if a player falls

//prototypes
void get_to_ground(object player);
void fall(object player, int falltime);

void
create_valley_room()
{
    set_short("On a wide ledge.\n");
    
    set_em_long("Standing on a wide ledge in the Blackwall mountains. "+
		"Jagged black cliffs extend skyward and drop some "+
		"twenty-five metres to the rocky valley floor below. "+
		"Though wide enough to walk along with ease, the "+
		"ledge is not very long; it extends only about twenty "+
		"metres horizontally. There is a thick growth of bushes "+
		"in the center of the ledge.\n");

    add_prop(ROOM_I_HIDE, 10); //only the bushes to hide in

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_item(({"growth", "thick growth", "bushes", "thick growth of bushes",
		   "branches", "broken branches", "crushed branches"}),
	     "This thick growth of bushes encompasses the entirety of a "+
	     "ten foot section of the ledge. The bushes are so thick that "+
	     "they entirely obscure ones view of the cliff face at that point. "+
	     "Upon closer inspection, you notice a number of broken and "+
	     "crushed branches in the patch.\n");
	    	     
    add_item(({"rocks", "rock", "boulders"}),
	     "The mountains are made of a coal-black basalt.\n");
    
    add_item(({"cliffs", "cliff", "cliff face"}),
	     "The cliff face stretches upwards for another hundred metres or "+
	     "more. There does not appear to be anything up there worth "+
	     "risking your life in such a long climb. It should be possible "+
	     "to climb down from the ledge, however.\n");  
}

/* Called when a player attempts to "climb" something.
   Hopefully he wishes to climb down the cliff.
*/

public int
climb_down(string arg)
{   
    int climb_ability; //the players ability to climb
    int falltime; // How long before the player falls, if
                  // he fails his climbing check.
    object player; //this_player();

    falltime = random(5);
    player = this_player();

    if ((arg == "down") || (arg == "down the cliff") ||
	(arg == "down to the ground") || (arg = "to the ground")) 

      //Command succeeds:
    {
	write("You begin the difficult task of climbing down to the "+
	      "valley floor.\n");
	say(QCTNAME(player) + " starts to climb down to the "+
	    "valley floor below.\n");
	tell_room(BLACKWALL_VALLEY1_DIR + "valley1_14", QCTNAME(player) + 
		  " begins to climb down from the ledge.\n");
	
	player->add_prop("_climbing_bandit_cliff", 1);
	player->add_prop(LIVE_S_EXTRA_SHORT, " is climbing down the cliff");
	
	/* We move the player to the ground before proceeding any further.
	   However, we use a no-glance on the look, and will cause the
	   player to look around after he has officially reached the ground.
	   The player is in valley1_14, not valley1_15 from now
	   on, however. No arrival messages will be printed as a direct
	   result of this move_living.
	*/

	player->move_living("M", BLACKWALL_VALLEY1_DIR + "valley1_14", 1, 1); 
	tell_room(BLACKWALL_VALLEY1_DIR + "valley14",
		  QCTNAME(player) + " begins to climb down from the ledge "+
		  "on the cliff face.\n", 0, this_player());

//Let us determine whether or not the player falls: Based on his dex, climb skill
//and encumberance.

	climb_ability = player->query_skill(SS_CLIMB) + 
	    (player->query_stat(SS_DEX) / 10) - 
	    (player->query_encumberance_weight() / 2);
	
	if (climb_ability + random(10) > 37)
	    // Anyone who has ever climbed knows the climb down is harder ;)    
	  
	{    //The player made it:
	
	    set_alarm(5.0, 0.0, &get_to_ground(player));
	}
    
	else
	{
	    //The player will fall, at some random point in the climb.
	
	    set_alarm(itof(falltime), 0.0, &fall(player, falltime));
	}
	
	return 1;	
    }

    // Command fails:

    notify_fail("Climb what?");
    return 0;
}

/* Does all the cleanup associated with a player who has finished climbing
   the cliff.
*/

void
get_to_ground(object player)
{
    //Remove climbing from description.
    player->remove_prop("_climbing_bandit_cliff");
    player->remove_prop(LIVE_S_EXTRA_SHORT);
    player->add_fatigue(-8); //Climbing is exhausting.
    player->catch_tell("You make it to the ground safely.\n");
    tell_room(this_object(), QCTNAME(player) + 
	      " makes it safely down the cliff.\n",
	      player, this_object());
    tell_room(BLACKWALL_VALLEY1_DIR + "valley1_14", QCTNAME(player) + 
	      " makes it safely down the cliff.\n", player,
	      this_object());
    set_this_player(player);
    player->do_glance();
      
    return;
}

/* Called when a player tries, but fails to climb the cliff
   and falls off. Deals damage to the player,  prints
   nifty messages and cleans up after climb_cliff().
*/

void
fall(object player, int falltime)
{
    int damage; //damage the player takes from the fall.
    int phurt;  //proportion of remaining hp lost in the fall

    write("You reach down for a foothold, but instead of finding "+
	  "one, you dislodge some loose stones, leaving yourself "+
	  "with nothing to stand on!!\n"+
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
		" only suffers from some cuts and bruises.\n");
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
	player->add_fatigue(-falltime); //Climbing is exhausting.
	set_this_player(player);
	player->do_glance();
    }
    return;
}

/* Called when a player tries to "enter" something, hopefully
   the cave. This function is also called when a player tries
   to search something. Searching the cave or the bushes is
   tantamount to entering them ;)
*/

int
enter_cave(string arg)
{
    if (arg == "cave" || arg == "the cave")
    {
	write("You force your way through the bushes and into the small cave mouth "+
	      "which they hide.\n");
	say(QCTNAME(this_player()) + " starts to push " +
	    this_player()->query_possessive() + " way into the bushes and "+
	    "quickly dissappears from view.\n");	
	this_player()->move_living("M", THIEF_LAIR_DIR + "cave1");
	return 1;
    }

    else
    {
	// We want different messages if the player merely enters the bushes. This
	// will still get them into the cave, however.

	if (arg == "bushes" || arg == "the bushes")
	{
	    write("You force your way into the bushes and discover that they "+
		  "conceal a small cave mouth. You make your way into the cave.\n");
	    say(QCTNAME(this_player()) + " starts to push " +
		this_player()->query_possessive() + " way into the bushes and "+
		"quickly dissappears from view.\n");
	    this_player()->move_living("M", THIEF_LAIR_DIR + "cave1");
	    return 1;
	}

	/* Command fails:
	   Notify_fail is not called, since the player might have been
	   searching the bushes.*/

	return 0;
    }
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
    add_action(drink_from_stream, "drink");
    add_action(climb_down, "climb");
    add_action(enter_cave, "enter");

/* Searching the bushes and/or cave will result in
   in entering the cave.*/
    add_action(enter_cave, "search");
}



