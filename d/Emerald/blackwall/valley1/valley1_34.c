/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <macros.h>
#include <tasks.h>
#include <formulas.h>

inherit "/d/Emerald/lib/search.c";
inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Stagnant pool.");
    set_em_long("At the very bottom of a gulley. A foul-smelling pool "+
		"of stagnant water resides here. The easiest way out "+
		"would be to return up the gulley.\n");

    add_item(({"pool", "algae", "sheen", "slime", "water"}),
	     "The pool is about ten metres in diametre. The depth of the "+
	     "pool cannot be ascertained due to the murkiness of the water. "+
	     "A sheen of slimy green algae covers much of the pool's surface "+
	     "and it emits a smell of stagnance and decay.\n");

    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n"); 

    add_item(({"ground", "earth", "down", "mud"}),
	     "The ground near the pool is muddy and slimy.\n");
		 
    add_search("pool", BLACKWALL_VALLEY1_DIR + "obj/ogre_skull"); 
 
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_33", "south", 0, 4);
}

/* Special smell for this room. */

public void
hook_smelled(string arg)
{
    if (!strlen(arg))
    {
	write("A smell of stagnance and decay pervades the area.\n");
	return;
    }
    
    if (parse_command(arg, ({}), "[the] 'pool' / 'slime' / 'algae' "+
        "/ 'water'"))
    {
	write("The pool positivly reeks of stagnation and rotting "+
	      "vegetable matter.\n");
    }
}
   

/* Players may attempt to drink from the slimy pool. It is probably not in
   their best interests, however. */
int
drink_from_pool(string str)
{  
// Is the player trying to drink from the pool?

    if (!(parse_command(str, ({}), "[water] 'from' [the] 'pool'")))
    {
	//command failed:
	notify_fail("Drink what from where?");
	return 0;
    }

/* Player will not drink from the player unless he is at less than half
   his soaked capacity. */

    if (this_player()->query_soaked() >
	(this_player()->query_prop(LIVE_I_MAX_DRINK) / 2))
    {
	write("You are not thirsty enough to to drink such a "+
	      "distasteful looking fluid.\n");
	return 1; //command succeeded, kinda ;)
    }

//Drinking from the pool:

    write("You drink a little water from the slimy "+
	  "pool. The water tastes even worse than it "+
	  "smells, and you feel as if a trail of "+
	  "slime has been left down your throat. You "+
	  "can barely keep from gagging.\n");
  
    say(QCTNAME(this_player()) + " drinks a little from the slimy pool! "+
	capitalize(this_player()->query_pronoun()) + " doesn't look so "+
	"good afterwards...\n");

    this_player()->drink_soft(25);
    
//Checking if the player will become sick.
    if (present("_valley34_puke_object", this_player()))
    {
	// the player will already become sick, do nothing more
	return 1;
    }

    if (this_player()->query_race() == "goblin")
    {
	// goblins live in filth and are more resistant to it, they
	// only need to pass a simple task against con to avoid illness
	if (this_player()->resolve_task(TASK_SIMPLE, ({TS_CON})) < 0)
	{
	    clone_object(BLACKWALL_DIR + "/obj/puke_object")->
		move(this_player());
	}
    }
    
    else
    {
	// others must pass a routine task against con
	if (this_player()->resolve_task(TASK_ROUTINE, ({TS_CON})) < 0)
	{
	     clone_object(BLACKWALL_DIR + "/obj/puke_object")->
		move(this_player());
	}
    }

    return 1; //drunk successfully
}

void
init()
{
    ::init();
    add_action(drink_from_pool, "drink");
}
