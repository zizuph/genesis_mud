/*
 * Meditation Room of the Elemental Temple of Calia
 * 
 * Created by Jaacar, June 2016
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit TEMPLE_ROOM_BASE;
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/lib/guild_support";

// Defines
#define LIVE_I_MEDITATING "_live_i_meditating"

// Prototypes

// Global Variables

public void
create_temple_room()
{
    set_short("Elemental Meditation Chamber");
    set_long("You have entered a very quiet room in the temple. "+
        "A sense of peace and tranquility emanates from the very "+
        "foundations of this room. The walls have several "+
        "wooden beams rising up to the ceiling. Suspended from "+
        "the wooden ceiling are massive glowing globes, providing the "+
        "illumination needed for meditation. A slender door leads east. "+
        "On the floor you see several mediation mats.\n\n");    
                   
    add_exit(ELEMENTALIST_TEMPLE + "outer10", "east");     
    
    try_item( ({ "mat", "mats", "mediation mat", "mediatation mats" }),
        "One the floor are several mediation mats made of a soft "+
        "material. You feel more peaceful just looking at them "+
        "however if you really want to relax, you could try "+
        "to <meditate> at one.\n");
       
    try_item( ({ "ceiling", "petrified wood", "beams", "wooden beams", 
    	"beam", "wooden beam" }),
        "The ceiling here is made from the same petrified wood as the rest "
      + "of the temple. However, here it does not form an arch, but has a "
      + "flattened roofing made from beams of petrified wood. The petrified "
      + "wood seems to have grown thin stalactites, and on the tip of each "
      + "stalactite a large globe of white fluorescent stone shines a "
      + "pleasant light throughout the chamber.\n");
      
   try_item( ({ "door", "sign", "slender door", "east" }),
        "A tall door, crafted by an intrinsic mix of dark oak and petrified "
      + "wood is rather slender. The door itself is also remarkably hefty, "
      + "likely to prevent sounds from the outside travelling into the chamber.\n");
    
    try_item( ({ "globes", "globe", "glowing globes", "glowing globe",
            "massive glowing globes", "massive glowing globe", "massive globe",
            "massive globes", "stalactites", "stones", "massive stones" }),
        "Suspended from stalactites, these globes are massive stones of an "
      + "unknown origin, radiating a strong yet pleasant glow that illuminates "
      + "the chamber.\n");
    
    try_item( ({"lever","small lever"}),"You notice a small lever on the side of "+
        "one of the beams. You might be able to pull it.\n");
    create_guild_support();
}

int
do_pull(string str)
{
	int taskone, tasktwo, taskthree, taskfour;
	
	if (!str)
        return 0;
	
	if (parse_command(str, ({}),"[the] [small] 'lever'"))
    {
		// If they aren't a Seeker, nothing will happen.
		if (!(GUILD_MANAGER->query_is_seeker(TP)))
		{
			write("Nothing happens.\n");
	        return 1;
	    }
	    taskone = (GUILD_MANAGER->query_can_do_wor_task_one(TP));
	    tasktwo = (GUILD_MANAGER->query_can_do_wor_task_two(TP));
	    taskthree = (GUILD_MANAGER->query_can_do_wor_task_three(TP));
	    taskfour = (GUILD_MANAGER->query_can_do_wor_task_four(TP));
	    
	    // If they haven't been assigned task one, nothing will happen.
	    if (!taskone)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task two, nothing will happen.
	    if (!tasktwo)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task three, nothing will happen.
	    if (!taskthree)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't been assigned task four, nothing will happen.
	    if (!taskfour)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they haven't already completed the pool part of task four, nothing will happen.
	    if (taskfour < 2)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // If they've already completed a further part of task four, nothing will happen.
	    if (taskfour > 2)
	    {
	    	write("Nothing happens.\n");
	        return 1;
	    }
	    
	    // They are indeed a Seeker and have been assigned task four and have not
	    // yet completed it.
	    GUILD_MANAGER->set_can_do_wor_task_four(TP, 3);
	    write("When nobody is watching, you quickly pull the lever. An image "+
	        "of a small switch quickly fills your mind. You notice the switch is "+
	        "on the underside of a table. You hear the words 'Earths Beholden'. "+
	        "You feel compelled to find this switch.\n");
	    return 1; 
	} 
	return 0;
}

public void
init()
{
    ::init();
    init_guild_support();
    add_action("gs_meditate", "meditate");
    add_action(do_pull, "pull");
}

void
gs_hook_start_meditate()
{
    write("You kneel down and close your eyes. A feeling of great "+
        "ease and self control falls upon you. You block off "+
        "your senses and concentrate solely upon your own mind. You "+
        "find yourself able to <estimate> your different preferences "+
        "and <set> them at your own desire.\nJust <rise> when you "+
        "are done meditating.\n");
    say(QCTNAME(this_player())+" kneels down on an empty mat and starts "+
        "to meditate.\n");
}

void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface "+
        "of your consciousness. You exhale and feel very relaxed as "+
        "you stand up.\n");
    say(QCTNAME(this_player())+" comes out of a trance and stands up.\n");
}
 
int 
query_prevent_snoop()
{
    return 1;
}
