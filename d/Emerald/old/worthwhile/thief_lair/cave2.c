/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/thief_lair/base_cave.c";

#define DIR "/d/Emerald/thief_lair/"

#include <stdproperties.h>

string wall_descrip = ("The walls, floor and ceiling of this cave are "+
                      "composed entirely of black basalt. They are rough "+
                      "in texture, suggesting an entirely natural origin. ");

void
create_banditcave_room()
{
    set_short("A cave, high in the Blackwall mountains.");
    set_em_long("A cave carved out of the black rock of the Blackwall "+
		"mountains. The air is distinctly more humid and stagnant "+
		"than that out in the open air. The cave seems to grow "+
		"larger to the north, but narrows to the south. If "+
		"one is quiet, the sound of running water may be heard.\n");

    Track_Descrip = "The occasional vague outline of a "+
              "footprint may be found on the floor of the cave.\n";

    Track_Difficulty = 38 + random(20);

    add_item(({"water", "sound", "running water", "sound of water",
		   "sound of running water"}),
	     "When listening carefully, the sound of running water "+
	     "can distinctly be heard from the north. It sounds "+
	     "like a bubbling brook.\n");
	     
    add_item(({"wall", "walls", "ceiling"}),
	     wall_descrip + "\n");
	     
    add_item(({"floor", "ground"}), wall_descrip + " " +
             "@@discover_tracks@@");

    add_item(({"footprints", "footprint", "outline", "outlines",
	     "vague outline", "vague outlines"}),
	     "A closer examination of the footprints reveals that they "+
	     "were made by booted feet of normal human (or elven, or "+
	     "orcish ... ) size. The number of footprints you can find "+
	     "on the generally hard surface of the cave suggests that "+
	     "many individuals have gone this way, heading both "+
	     "north and south.\n");

    add_exit(DIR + "cave3", "north", 0, 1);
    add_exit(DIR + "cave1", "south", 0, 1);  
}





