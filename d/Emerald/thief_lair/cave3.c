/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/thief_lair/base_cave.c";

#include <stdproperties.h>

#define DIR "/d/Emerald/thief_lair/"

void
create_banditcave_room()
{
    set_short("At a junction, in a cave.\n");
    set_em_long("At the southeast corner of a large, underground "+
		"cavern. To the west, a ledge extends along the southern "+
		"wall of the cavern, while passages extend away from the "+
		"cavern to the south, and northeast. The sound of running "+
		"water echoes up from below.\n");

    Track_Descrip = "The occasional vague outline of a "+
		    "footprint may be found on the ledge.\n";

    Track_Difficulty = 25 + random(20);

    add_item(({"sound", "running water", "sound of water",
		   "sound of running water"}),
	     "You expect that an underground stream must traverse "+
	     "the floor of the larger portion of the cavern which "+
	     "remains out of sight, below and to the west.\n");
	
    add_item(({"wall", "walls"}),
	     "The cave is carved out of a black volcanic rock. In places, "+
	     "water drips from the walls and patches of green moss can be "+
	     "found growing wherever moisture and crevices permit.\n");

    add_item("ledge",
	     "A wide ledge juts out along the southern wall of the cavern "+
	     "which opens up to the northwest. The ledge is thirty feet or "+
	     "more above the cavern floor, but is sufficiently wide to "+
	     "allow safe travel.\n");

    add_item(({"floor", "ground"}),
	     "The floor consists of an unevern ground of hard, black rock "+
	     "and is dotted with an occasional puddle or patch of green "+
	     "moss. " + "@@discover_tracks@@");
	
    add_item(({"footprints", "footprint", "outline", "outlines",
	     "vague outline", "vague outlines"}),
	     "A closer examination of the footprints reveals that they "+
	     "were made by booted feet of normal human (or elven, or "+
	     "orcish ... ) size. The number of footprints suggests "+
	     "many creatures passed this point, heading west along "+
	     "the ledge, and south, down the passage. You find no "+
	     "footprints suggesting that anything travelled "+
	     "northeast.\n");

    add_item("cavern",
	     "The cavern extends perhaps about a hundred metres north "+
	     "and is upwards of 50 metres wide at its greatest. The "+
	     "cavern is very damp, and you can see a great cover of "+
	     "green moss on the cavern floor.\n");

    add_item(({"moss", "green moss"}),
	     "It is  a harmless seeming moss, dark-green in color. The "+
	     "sort which commonly carpets the ground in dark, wet "+
	     "places.\n");

    add_cmd_item(({"moss", "green moss"}), ({"eat"}),
             "You carefully pick some of the moss, then stick it "+
	     "cautiously in your mouth.\nYuck! It tastes terrible!\n");

    add_item(({"passages", "passage"}),
	     "Which passage do you wish to examine, the one which "+
	     "leads northeast, or the one which leads south?\n");

    add_item(({"south passage", "southern passage"}),
	     "The passage which leads to the south seems to "+
	     "gradually become narrower, with distance from this "+
	     "cavern.\n");

    add_item(({"northeast passage", "northeastern passage"}),
	     "The passage to the northeast is more of an extension "+
	     "of the cavern, only at this particular height.\n");

    add_exit(DIR + "cave4", "northeast", 0, 1);
    add_exit(DIR + "cave2", "south", 0, 1);
    add_exit(DIR + "cave5", "west", 0, 1);
}


