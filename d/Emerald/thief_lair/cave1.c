/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

#define VALLEY1_DIR "/d/Emerald/blackwall/valley1/"

inherit "/d/Emerald/thief_lair/base_cave";

string Wall_Descrip = ("The walls, floor and ceiling of this cave are "+
                      "composed entirely of black basalt. They are rough "+
                      "in texture, suggesting an entirely natural origin."); 

int
leaving_cave()
{
    write("You force your way through the thick bushes at the mouth of the "+
	  "cave.\n");
    return 0;
}

void
create_banditcave_room()
{ 
    int ran; // A random number.
  
    set_short("A narrow, low-ceilinged cave.");
    set_em_long("At the mouth of a narrow, low-ceilinged cave. To the "+
		"south lies the cave entrance, while to the north, the "+
		"cave seems to gradually expand. There is no telling "+
		"how far this cave might extend into the mountain.\n");

    Track_Descrip = "You notice an occasional footprint on the floor "+
	"of the cave.\n";
    Track_Difficulty = 40 + random(20);

    add_item(({"entrance","cave mouth","mouth","cave entrance"}),
        "Thick bushes prevent easy exit from the cave.\n");

    add_item(({"bushes", "bush"}),
	     "A thick growth of bushes hides the cave-mouth from external "+
	     "view.\n");

    add_item(({"wall", "walls", "ceiling"}),
	     Wall_Descrip + "\n");
	     
    ran = 40 + random(20);

    add_item(({"floor", "ground"}), Wall_Descrip + " " +
            "@@discover_tracks@@");

    add_item(({"footprints", "footprint", "outline", "outlines",
	     "vague outline", "vague outlines", "tracks"}),
	     "A closer examination of the footprints reveals that they "+
	     "were made by booted feet of normal human (or elven, or "+
	     "orcish ... ) size. The number of footprints you can find "+
	     "on the generally hard surface of the cave suggests that "+
	     "many individuals have gone this way, heading both deeper "+
	     "into the cave, and leaving it.\n");

    add_exit(THIEF_LAIR_DIR + "cave2", "north", 0, 1);
    add_exit(VALLEY1_DIR + "valley1_15", "south", leaving_cave, 1, 0);
}

void
init()
{
    :: init();
    if (interactive(this_player()))
	catch(call_other(THIEF_LAIR_DIR + "bandit_clone_handler", "??")); 
}







