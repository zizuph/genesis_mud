/* A valley in the southern Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <macros.h>

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Beside a waterfall in the Blackwall mountains.\n");
    set_em_long("In a river valley in the southern Blackwall mountains. "+
		"This is the site of a spectacular waterfall. The swift "+
		"flowing river plummets in excess of twenty metres into "+
		"a deep pool of churning water. Cliffs of coal black "+
		"basalt line the falls. Fortunately, it is possible to "+
		"circumvent the cliffs, allowing one to continue to travel "+
		"upstream. The roar of the falling water drowns out all other "+
		"sound.\n"); 

    set_river_room();

    add_item(({"fall", "falls", "waterfall", "waterfalls",
		 "sheets of crystal clear water", "sheets of water"}),
	     "The waterfall represents a spectacular sight. Sheets of crystal "+
	     "clear water plummet from above you to land with a resounding "+
	     "roar in the pool at your feet.\n");
    
    add_item(({"cliff", "cliffs", "horseshoe shaped cliff", "horseshoe",
		 "horseshoe cliff", "shaped cliff"}),
	     "The waterfall has cut into the bedrock, exposing sheets "+ 
	     "of black basalt. The bedrock forms a horseshoe "+
	     "shaped cliff with the waterfall at its apex.\n");    

    add_item("river", 
	     "The river flows from west to east along a valley between "+
	     "two mountains.\n");

    add_item("pool",
	     "A frothy pool, perhaps as deep as ten metres, has been "+
	     "carved out of the bedrock at the base of the waterfall.\n");

    add_item(({"rock", "bedrock", "black rock", "black bedrock"}),
	     "The mountains are composed primarily of a coal black "+
	     "basalt, no doubt of volcanic origin.\n");
    
    add_item(({"mountains", "blackwall mountains"}),
      "You are at the edge of the southern extreme of the Blackwall "+
      "mountains. A forest of deep black peaks dominates to the North. "+
      "Two mountains line either side of the valley. The northern one "+
      "is the taller of the "+
      "two, its jagged peak jutting skyward as if to lacerate the "+
      "clouds. The southern one is much less impressive, standing "+
      "not nearly so tall, and with a flattened top. Still, its face is "+
      "marred by stark black cliffs, and it would be no easy conquest.\n");

    add_cmd_item(({"cliff", "cliffs"}), "climb",
        "You can travel further up the valley without climbing the "+
        "cliffs, so why bother?!\n");
    
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_10", "northeast", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_8", "west", 0, 3);
}

/* Modified from the version found in base_valley.c so that players may
   drink from the pool as well.
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
	!parse_command(where, ({}), "[the] 'pool'"))
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
	      "chill of the pool and then bring the cold fluid up to "+
	      "your mouth. The water tastes as refreshing as it feels.\n");
 
	say(QCTNAME(this_player()) + "drinks some water from the stream.\n");
	return 1;
    }
}                           

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}





