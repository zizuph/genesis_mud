/* 
 * NP1, Crossroad leading to the Aghar or Dewar.
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_ROAD_BASE;

/*
 * Function name: reset_pal_road_room
 * Description  : Resets the room
 */
void
reset_pal_road_room()
{
	
}

/*
 * Function name: create_pal_road_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_road_room()
{
    set_short("Crossroads");
    set_long("You are the end of the road. To your north lies an "
    +"old cavern that appears to be well-kept and well "
    +"lit. To the south lies a old abandoned mine. The stench coming "
    +"from the mine is horrific and the lights "
    +"seem to flicker.\n");
	    
    add_item(({"mine", "mines", "abandoned mine","dump","refuse","signs"}), 
	"The mine appears to have been abandoned and turned into an "
    +"old refuse dump.  There are signs of life in there and you can "
    +"hear joyful singing and noises coming from "
    +"within the mine.\n");
    add_item(({"cave", "caverns", "well-kept caverns", 
    "well-kept caves", "old cavern", "cavern", "well-lit cavern",
	"well-lit caverns"}), "An old deep cavern system "
    +"that appears to be well-kept.  There are obvious "
    +"bloodstains outside of the cavern and you can "
    +"hear cursing and scowling from inside the cavern. The cavern "
    +"itself looks well lit by well-maintained lantern "
    +"system.\n");
	add_item(({"tree", "trees", "pine", "pines", "spruce", "spruces",
	"pine trees", "spruce trees", "spruce tree", "pine tree", "huge tree",
	"huge trees"}), "Tall pine and spruce trees with there evergreen needle "
	+"rest atop the sheer stone walls which line either side of this "
	+"road\n");
	add_item(({"wall", "sheer walls", "stone walls", "stone wall", 
	"sheer wall", "sheer stone wall", "sheer stone walls","stone"}),"Tall "
	+"stone walls rising about 20 feet up line either side of the road. "
	+"Sitting atop the walls are trees.\n");
    
       
    add_exit(RDIR + "aentrance","south","@@inaghar",0);
    add_exit(RDIR + "dentrance","north","@@indewar",0);
    add_exit(RDIR + "np2","east",0);
    reset_pal_road_room();
	    
}

public int
indewar()
{
	write("As you step off the road into the cavern you are greeted with "
	+"a cool breeze. The temperature has fallen slightly and the "
	+"crisp air of the outdoors has been left behind.\n");
	return 0;
}

public int
inaghar()
{
	write("As you step off the road into the abandoned mine you are greeted "
	+"by the most putrid smell you have ever smelt. The warm putrid air flows "
	+"around you making you long for the crisp air of the outdoors that has "
	+"been left behind.\n");
	return 0;
}

