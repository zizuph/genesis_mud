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
    set_short("On a ledge in a large, humid cavern.");
    set_em_long("On a wide ledge on the south wall of a large underground "+
		"cavern. Damp, mossy walls lead both up from the ledge "+
		"and down to the cavern floor below. The ledge extends "+
		"both east and west. Passages leading away from this "+
		"cavern branch off from this ledge to the west. The sound "+
		"of running water echoes up from below.\n");
	
    add_item(({"wall", "walls"}),
	     "Moss and moisture line the walls of this cavern. Water "+
	     "trickles down the walls to the ledge, pooling momentarily "+
	     "before continuing down to the cavern floor. Dark green moss"+
	     "grows wherever it can get a hold on the black, rocky surface.\n");
	     	    
    add_item("ledge",
	     "Though slippery in places due to the moisture, the ledge is "+
	     "sufficiently wide to traverse safely.\n");

    add_item("cavern",
	     "The cavern extends perhaps about a hundred metres north "+
	     "and is upwards of 50 metres wide at its greatest. The "+
	     "cavern is very damp, and you can see a great cover of "+
	     "green moss on the cavern floor. "+
	     "A stream runs along the western edge of the cavern.\n");

    add_cmd_item(({"wall", "walls", "down", "up"}), ({"climb", "climb down",
							"climb up"}),
		 "Considering the slipperiness of the wet rock, and the "+
		 "difficulty of finding a good hand-hold amongs the "+
		 "moss you decide that either climbing up the wall, or "+
		 "down to the cavern floor would be excessivly dangerous.\n");

    add_item(({"moss", "green moss"}),
	     "It is  a harmless seeming moss, dark-green in color. The "+
	     "sort which commonly carpets the ground in dark, wet "+
	     "places.\n");

    add_cmd_item(({"moss", "green moss"}), ({"eat"}),
             "You carefully pick some of the moss, then stick it "+
	     "cautiously in your mouth.\nYuck! It tastes terrible!\n");

    add_item("stream",
	     "A stream traverses the cavern floor, meandering along "+
	     "the western wall.\n");

    add_item(({"sound", "running water", "sound of water",
		   "sound of running water"}),
	     "You expect that an underground stream must traverse "+
	     "the floor of the larger portion of the cavern.\n");
	
    add_exit(DIR + "cave3", "east", 0, 1);
    add_exit(DIR + "cave6", "west", 0, 1);
}


