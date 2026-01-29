/* Base room for the valley1 portion of the Blackwall mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/std/room";
 
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/sys/weather.h"

void
create_valley_room()
{
    add_item(({"ground", "soil", "rich soil", "black soil",
		   "rich black soil", "down"}),
	     "The ground is composed of a rich black soil which seems "+
	     "ideal to supporting plant life.\n");
    
    add_item(({"sky"}),
	     WEATHER_DESC_SKY + "\n");

     //Forests are easy places to hide in, therefor: 
    add_prop(ROOM_I_HIDE, 3);
}

/* Set in certain rooms which correspond to higher, rocky
   ground. */

void
set_highvalley_room()
{
    remove_item("ground");

    add_item(({"ground", "down"}),
	     "The ground is beneath your feet is rocky, with only the "+
	     "occasional patch of soil allowing for the growth of "+
	     "vegetation.\n");
}
	     

/* Function called during the creation of rooms which contain a river.
   Sets up a couple of standard properties, and add_items.
*/
void
set_river_room()
{
    remove_item("sky");
    add_item("sky",
	     "You are afforded a clear view of the sky thanks to the break "+
	     "in the forest afforded by the river. + WHEATHER_DESC_SKY + \n");
    
// Okay, not quite a beach, but shares similiar properties, namely 
// adjacency to water:
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

// There is water in an effectively infinite supply of water in this room.
    add_prop(OBJ_I_CONTAIN_WATER, -1);

/* These properties are set so that players with bottles, for example,
   could fill them with water here (if the bottle is so coded). They
   could also wash their hair here, etc.
*/
}

nomask void
create_emerald_room()
{   
    create_valley_room();
}

/* Default smell for rooms in the valley. */

public void
hook_smelled(string arg)
{
    if (strlen(arg) && !(parse_command(arg, ({}), "[the] 'forest' / " +
        "'woods' / 'plants' / 'trees' / 'bushes' / 'flowers' "))) 
    {
        return;
    }
    
    // player may "smell woods", "smell the plants" etc. and will
    // receive the same message
	
    write("A complex sea of aromas fills the forest air. Pollens, "+
	  "both sweet and offensive issue from various plants and "+
	  "flowers, while the quiet smell of decay and rebirth "+
	  "permeates the whole area.\n");
}


/* Allows players to drink from the river which flows through much
   of the valley.
   Returns 1 (true) or 0 (false) depending upon
   whether or not the player succesfully drank from the river.
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

// Modification to the the function in base_valley is made here:

    if (where && !parse_command(where, ({}), "[the] 'river'") &&
	!parse_command(where, ({}), "[the] 'stream'"))
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
	      "chill of the river and then bring the cold fluid up to "+
	      "your mouth. The water tastes as refreshing as it feels.\n");
 
	say(QCTNAME(this_player()) + "drinks some water from the stream.\n");
	return 1;
    }
}      
                 






