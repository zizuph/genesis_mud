/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains. This cavern contains a platform which allows the movement
   of goods between it and cave7. 

   Code (c) 1999 to Damian Horton - BKA Casimir,
   Platform idea and code by Shiva.
*/
 
#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include "/d/Emerald/sys/paths.h"

inherit THIEF_LAIR_DIR + "base_cave.c";

string Wall_Descrip = ("The walls, floor and ceiling of this cave are "+
		       "composed entirely of black basalt. Water trickles "+
		       "down them in places, occasionally forming small "+
		       "puddles on the floor. Where there is sufficient "+
		       "moisture, a thick green moss grows abundantly. "+
		       "The cavern appears to be of an entirely natural "+
		       "origin.");

/* Simple function which allows for a slight variation in the description
   of the mechanism, depending upon the presence of the platform which
   runs between cave6 and cave7.
*/

string
mechanism_descrip()
{

    if (present("thief_lair_platform"))
    {
	return ("The platform is securely fastened to twin rails which " +
		"extend down the cliff face to the cavern floor. The set of "+
		"ropes and pulleys is connected to the platform. There is "+
		"no obvious means of working the mechanism.\n");
    }
    
    return ("Twin metal rails extend down the cliff face to the cavern "+
	    "floor. A sequence of ropes and pulleys dangles down to "+
	    "some sort of wooden platform which rests on the ground at "+
	    "the base of the cliff. It appears that the platform, rails, "+
	    "and pulley system are all interconnected. There is no "+
	    "obvious means of activating the mechanism.\n");
}


/* Function to prevent anyone who is carrying too much from climbing
   down the rope ladder. More importantly, this function sets up the
   reactions of the bandits who await in ambush at the base of the 
   ladder in cave7.
*/

public int
block_down()
{
    if (this_player()->query_prop(OBJ_I_WEIGHT) > 90000)
    {
        write("As you step onto the ladder, you notice the ropes tighten, " +
            "barely able to hold your weight.  It is far too dangerous " +
            "to continue down.\n");
        return 1;
    }

    return 0;
}

void
create_banditcave_room()
{
    set_short("On a ledge in a large, humid cavern.");
    set_em_long("On a wide ledge overlooking a large, humid cavern. "+
		"The ledge extends to the west, with the only other "+
		"possible direction of travel being downwards. "+
		"Fortunatly, someone has left a rope ladder here, which "+
		"dangles down the slippery cliff face. The sound of "+
		"running water echoes up to you from directly below.\n");

    add_item(({"sound", "running water", "sound of water",
		   "sound of running water"}),
	     "The sound suggests that an underground stream runs at the "+
	     "base of the cliff. Peering over the edge, you notice that "+
	     "a stream does flow across the larger cavern floor, not "+
	     "far from the base of the rope ladder.\n");

    add_item(({"wall", "walls", "ceiling"}),
	     Wall_Descrip + "\n");
	     
    add_item("floor", Wall_Descrip + " Wear and tear on the ground beside "+
	     "the rope ladder suggests that the it has been used more "+
	     "than once.\n");
    
    add_item(({"ledge", "wide ledge"}),
	     "You are standing on a wide ledge, at the edge of a "+
	     "wet, mossy cliff which descends into the darkness "+
	     "below you. Though the floor is slippery in places "+
	     "due to moss and moisture, there is no danger of "+
	     "falling off the ledge, for it is  several metres "+
	     "in width between the cavern walls, and the cliff face.\n");

    add_item(({"cliff", "drop off", "face", "cliff face"}),
	     "The cliff extends thirty or more feet to the "+
	     "cavern floor below you. Water trickles down much of "+
	     "the cliff face and though there are some ledges "+
	     "which someone brave enough to climb it could "+
	     "use as foot and handholds, these are rendered "+
	     "useless by the abundance of moss. Fortunatly, "+
	     "someone has placed a rope ladder which one may "+
	     "use to descend the cliff. Beside the ladder are "+
	     "two metal rails and a curious mechanism consisting "+
	     "of ropes and pulleys.\n");

    add_cmd_item("cliff", ({"climb", "climb down"}),
		 "Bruises, broken bones, and other serious "+
		 "injuries await you if you fall off the cliff. "+
		 "The rope ladder looks to be a much safer "+
		 "method of descending the cliff.\n");

    add_item(({"water", "trickles of water", "moisture"}),
	     "In many places, the walls are lined with moisture, "+
	     "as water trickles down them from "+
	     "above. In most places, there is just enough water "+
	     "to make things slippery. There is certainly not "+
	     "enough to drink, or otherwise make use of. The "+
	     "occasional puddle forms on the ledge, but more "+
	     "often, where there is any possible accumulation "+
	     "of water, one finds moss instead.\n");

    add_item(({"moss", "green moss"}),
	     "It is  a harmless seeming moss, dark-green in color. The "+
	     "sort which commonly carpets the ground in dark, wet "+
	     "places.\n");

    add_cmd_item(({"moss", "green moss"}), ({"eat"}),
             "You carefully pick some of the moss, then stick it "+
	     "cautiously in your mouth.\nYuck! It tastes terrible!\n");

    add_item(({"puddle", "puddles", "pools"}),
	     "The moisture which trickles down the walls of the "+
	     "occasionally forms small pools along the ledge, "+
	     "before trickling across the ledge and then down "+
	     "the cliff into the cavern below. The puddles are "+
	     "not very deep and not very interesting.\n");

    add_item(({"ladder", "rope ladder", "rope"}),
	     "A ladder, made of thick hemp rope descends the cliff "+
	     "face into the darkness below. It looks to be sturdy "+
	     "enough, but just the same, you would not want to "+
	     "push your luck by climbing down it while carrying too "+
	     "much.\n");
		
    add_item(({"strange mechanism", "mechanism", "pulleys", "ropes "+
		 "and pulleys", "rails", "metal rails",
		 "rope and pulley system"}),
	     mechanism_descrip);

    add_exit(THIEF_LAIR_DIR + "cave3", "east", 0, 1);
       
    clone_object(THIEF_LAIR_DIR + "obj/platform")->move(this_object(), 1);
  
    reset_room();   
}

public int
climb_ladder(string arg)
{   

    object bottom; //room at the bottom of the ladder

    if ((arg == "down") || (arg == "ladder") || (arg == "down ladder") 
	|| (arg == "down the ladder"))
    {

// Make sure the player is not in combat, and is not too heavy for the ladder:

	if (!(block_down()))
	{
// He isn't:
	    this_player()->move_living("down", THIEF_LAIR_DIR + "cave7", 1, 0);

	    bottom = find_object(THIEF_LAIR_DIR + "cave7");
	    bottom->start_conversation(this_player());
	    return 1;
	}
    }

    // Command fails.
    notify_fail("Climb what?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(climb_ladder, "climb");
}




