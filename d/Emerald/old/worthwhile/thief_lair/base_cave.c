/* Base room for the bandits caverns in the Blackwall mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/std/room";
 
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

//global variables

string Track_Descrip; /* A string describing tracks which players _might_
			 see on the ground - see discover_tracks() below.
		      */

int Track_Difficulty; /* tracking skill required to find tracks on the
			 ground */
void
create_banditcave_room()
{
}

nomask void
create_emerald_room()
{
    add_item(({"rock", "basalt", "black rock", "black basalt"}),
	     "The cave has been carved out of the black basalt which makes "+
	     "up the majority of the upper reaches of the Blackwall "+
	     "Mountains. Volcanic in "+
	     "origin, the stone is a dull, coal black color and "+
	     "reflects almost no light.\n");
	
    add_prop(ROOM_I_INSIDE, 1);
    
    create_banditcave_room();
}


/* Used to add additional descriptions of tracks to add_items in rooms, 
   if the player examining the item in question (usually the floor ;)
   has enough skill to notice such things.
   
   Arg: int skill_needed - The tracking skill required for a player to
                           notice the tracks.
   
   returns string:
           Track_Descrip if the player has sufficient skill,
           "\n" if he does not.
*/

string 
discover_tracks()
{
    if (this_player()->query_skill(SS_TRACKING) > Track_Difficulty)
    {
	return Track_Descrip;
    }
    	
    return "\n"; 
}

/* Allows players to drink from the stream in certain portions of the 
   bandit caves. Returns 1 (true) or 0 (false) depending upon
   whether or not the player succesfully drank from the stream.
   Modified from /d/telberin/rose/rosefountain.c by Shiva/Marisol 
*/

int
drink_from_stream(string str)
{
    string what, where; // Parsed portions of the player input.  
    int i; // Loop indices.

    if (!strlen(str))
    {
	notify_fail("Drink (from) what?\n");
	return 0;
    }

    /* See if syntax is "drink <something> from <something>" */
    if (sscanf(str, "%s from %s", what, where) != 2)
    {
        /* See if syntax is "drink from <something>" */
        if (!sscanf(str, "from %s", where))
	{
            /* Syntax must simply be "drink <something>" */
            what = str;
	}
    }

    if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
    {
        notify_fail("Drink (from) what?\n");
        return 0;
    }

    if (where && !parse_command(where, ({}), "[the] 'stream'"))
    {
        /* Technically, this isn't going to show because of the standard
         * 'drink' command.  Really, there's not much choice, though,
         * since we don't want to return 1.
         */
        notify_fail("Drink from where?\n");
        return 0;
    }
    
/* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
	{
            /* Can't drink any more */
            break;
	}
    }

    if (i == 0)
    {
        write("You are not thirsty.\n");
        return 1;
    }
  
    else
    {
        write("Cupping your hands, you dip them into the refreshing "+
	      "chill of the stream and then bring the cold fluid up to "+
	      "your face. Though a little gritty, the water of the "+
	      "stream is quite enjoyable.\n");
 
	say(QCTNAME(this_player()) + "drinks some water from the stream.\n");
	return 1;
    }
}                           





