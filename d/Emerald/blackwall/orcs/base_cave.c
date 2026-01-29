/* Base room for the orc holy cavern in the Blackwall mountains.
   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Emerald/sys/paths.h"

int river_room; //determines if there is a river flowing this cavern, in
                //particular this is necessary to allow the river to have
                //a smell per the generic hook_smelled function in this file

/* Replaces create_emerald_room() in rooms which inherit from this base. */
void
create_cave()
{   
}

/* Sets up a few things referring the portions of the cavern through 
   which the river floors.
*/
 
void
set_river_room()
{
    river_room = 1;

// Okay, not quite a beach, but shares similiar properties, namely 
// adjacency to water:
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

// There is water in an effectively infinite supply of water in this room.
    add_prop(OBJ_I_CONTAIN_WATER, -1);

/* These properties are set so that players with bottles, for example,
   could fill them with water here (if the bottle is so coded). They
   could also wash their hair here, etc.
*/
    add_item(({"river", "stream", "underground river", "underground stream",
		   "water", "brownish water"}),
	     "A small, shallow river, about twenty feet across flows "+
	     "along the western wall of the cavern. "+
	     "The water has taken on a brownish hue. The river is shallow "+
	     "and flows fairly quickly across the cavern floor.\n");
	     
}
	
/* Sets up the default conditions and items for inheriting rooms. */
nomask void
create_emerald_room()
{      
    add_item(({"ground", "floor", "cavern floor", "down"}),
	     "The cavern floor has been carved out of black rock via many "+
	     "years of water action. It is rough and uneven, with "+
	     "pools of moisture forming at the low points. Slime and moss "+
	     "cover much of the ground, particularly in the vicinity of "+
	     "those pools.\n");

    add_item(({"pools", "pools of water"}),
	     "Water pools in the lowest nooks and crevices of the cavern "+
	     "floor. Moss, mold and algae line these pools.\n");

    add_item(({"algae"}),
	     "Growths of yellowish algae fill the small pools of water "+
	     "which can be found at locally low points along the cavern "+
	     "floor.\n");

    add_item(({"ceiling", "up"}),
	     "The cavern extends as much as ten metres vertically, "+
	     "at its centre, though in places, particularly near the "+
	     "pillars of stone and the cavern walls, it barely affords "+
	     "enough room for you to stand.\n");

    add_item(({"walls", "wall"}),
	     "The walls, floor and ceiling of the cavern are composed of "+
	     "a black basalt. The walls glisten with moisture in places, "+
	     "and are covered with moss, or mold in many others.\n");
    
    add_item(({"stone", "rock", "basalt", "black basalt"}),
	     "This cavern has been carved out of the black rock which "+
	     "gave rise to the mountains name: Blackwall.\n");

    add_item(({"moss", "molds", "mold", "moss and molds"}),
	     "Several different species of mold and moss can be found "+
	     "in the cavern.\n");

    add_prop(ROOM_I_LIGHT, -1); //one level of darkness in the room

    river_room = 0;

    create_cave(); /* done last so that everything in it can over write the
		      defaults found here */
}

/* Default smell for rooms in the cavern. */
public void
hook_smelled(string arg)
{
    if (river_room && ((arg == "river") || (arg == "stream") || 
	(arg == "water")))
    {
	write("The river doesn't smell particularly good, though perhaps "+
	      "it is because you cannot get the overall scent of the "+
	      "cavern out of your nose.\n");
	return;
    }
  
    else if (strlen(arg))
    {
	// player attempted to smell something in the room other than
	// water
	return;
    }

    // player smelt the room in general:

    write("The stagnant cavern air is filled with a myriad of unpleasant "+
	  "smells. The smells of molds and mildews mingle with "+
	  "another scent which closely resembles that of "+
	  "day old feces.\n");
}

/* Players may attempt to drink from the river in those rooms through
   which it passes. Not recommended unless you are a  goblin who is used to
   such filthy water, however.
*/

int
drink_from_river(string str)
{  
// Is the player trying to drink from the pool?

    if (!(parse_command(str, ({}), "[water] 'from' [the] 'stream' / "+
			"'river'")))
    {
	//command failed:
	notify_fail("Drink what from where?");
	return 0;
    }

/* Drinking from the river. Note that goblins can drink from this river
   without thinking, and without the possibility of suffering from some
   ill-effect. */
    
    if (! (this_player()->query_race() == "goblin") &&
	 ! (this_player()->query_prop("_drunk_from_Emerald_orc_river")))
    {
	// player is not a goblin, and hasn't tried to drink from the
	// river before

	write("You crouch to drink from the river, but the unpleasant "+
	      "appearance and smell of the water makes you think twice.\n");
	say(QCTNAME(this_player()) + " crouches to drink from the "+
	    "river but seems to be having second thoughts.\n");
	// if the player tries to drink again we will let him:
	this_player()->add_prop("_drunk_from_Emerald_orc_river", 1);
    }

    else
    {
	if  (this_player()->drink_soft(100))
	{
	    write("You drink a little from the river. The taste of the "+
		  "water is not exactly pleasant.\n");
	    say(QCTNAME(this_player()) + " drinks from the river.\n");
	}
	
	else
	{
	    write("You are not thirsty.\n");
	}
	
	if (this_player()->query_race() == "goblin")
	{	       
	    return 1; //do nothing more, goblins will not become sick
	}
	    
//Checking if the player will become sick.
	if (present("_valley34_puke_object", this_player()))
	{
	    // the player will already become sick, do nothing more
	    return 1;
	}
    
	else
	{
	    // others must pass a simple task against con
	    if (this_player()->resolve_task(TASK_SIMPLE, ({TS_CON})) < 0)
	    {
		clone_object(BLACKWALL_DIR + "/obj/puke_object")->
		move(this_player());
	    }
	}
    }
    
    return 1; //drunk successfully
}

/* This function is called when a player attempts to enter the shrine,
   cave6.c. It is called in add_exit in the adjacent rooms.
   If a player has been thrown out of the shrine for blasphemy by the
   shrine's supernatural guardian, he or she will be unable to enter
   the shrine. This function checks for a property in the player, thus
   a player will be able to reenter the shrine after logging out.
*/
int
safeguard_shrine()                 
{
    if (this_player()->query_prop("_defiled_shrine_to_vs"))
    {
	write("You find that you are simply unable to will yourself "+
	      "to approach the altar once again.\n");
	return 1; // do not move the player
    }
    
    return 0; //move the player into the room as normal
}
      







