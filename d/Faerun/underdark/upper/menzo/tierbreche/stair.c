/*
 *  faerun/underdark/upper/menzo/tierbreche/stair.c
 *
 *  
 *  Created by Midnight, 12-2-2004
 */

#include "defs.h"

inherit P_MENZO_TIERBRECHE + "std/base_room";

/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Tier Breche
 */
void create_tierbreche_room()
{
	set_short("At the bottom of the stair");
	set_long("A wide impressive stair raises steeply up before you, " +
                 "towards the Tier Breche, the plateau high above the rest "+
                 "of the city. It houses the drow Academies of Menzoberranzan. " +
		 "The stair opens up in a several feet high beautiful " +
		 "archway and decorations have been carved " +
		 "into the arch. The arch is supported by swirling " +
		 "columns made of natural stalagmites.\n");
		 
	add_item(({"stair", "stairs"}),
        "This is a grand stair made of natural stone and it looks " +
        "as if it's been carved directly into the mountain. " +
        "It's raised towards the plateau of Tier Breche with " +
        "a few dozen steps to climbs to reach the top.\n");

        add_item(({"plateau"}),
        "This is the Tier Breche. You can spot three buildings " +
        "on top of the plateau. The plateau is the highest point " +
        "on the floor of this two-mile cavern.\n");
        
        add_item(({"buildings"}),
        "On top of the plateau you can spot three very different " +
        "buildings. One gracefully curving many-spired tower, one " +
        "giant building shaped like a pyramid and finally an " +
        "intriguing building shaped like a giant spider.\n");
        
        add_item(({"arch", "archway"}),
        "The arch is rested upon two high columns which are " +
        "standing on each side of the wide stair. Beautiful " +
        "drowish decorations has been carved into the arch .\n");
        
        add_item(({"decorations", "drowish decorations"}),
        "Drowish decorations are carved into the arch. They " +
        "glow with a soft purple colour.\n");
        
        add_item(({"columns"}),
        "There are a several feet high column on each side " +
        "of the wide stair. They are carved out of natural " +
        "stalagmites.\n");
        
        add_exit(P_UPPERDARK + "dark_dom/room/u48", "southeast");
        add_exit("plateau1", "stair");
       
}