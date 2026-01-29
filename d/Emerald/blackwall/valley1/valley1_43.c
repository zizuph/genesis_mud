/* A valley in the southern Blackwall mountains.
   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{   
    ::create_valley_room();
    set_short("Stony valley in the Blackwall mountains.");
    set_em_long("In a stony valley in the southern portion of the "+
		"Blackwall mountains. Little vegetation grows in the "+
		"shadow of the overhanging mountains. The valley "+
		"slopes gently downward to the east.\n");
 
    set_highvalley_room();

    add_prop(ROOM_I_HIDE, 10); //little cover

    add_item(({"plants", "vegetation", "bushes", "grass", "tufts",
		 "tufts of grass", "bush", "patches", "patches of moss",
		 "cover", "scant vegetative cover", "scant cover", 
		 "vegetative cover"}),
	     "Tufts of grass, patches of moss, and the occasional bush "+
	     "can be found in the valley.\n");
	    	     
    add_item(({"rocks", "rock", "black rock"}),
	     "The mountains are made of a coal-black basalt.\n");

    add_item(({"stones", "loose stones"}),
	     "Stones of all shapes and sizes litter the valley floor. They "+
	     "are composed of the same black rock as the surrounding "+
	     "mountains.\n");    
    
    add_item(({"mountains", "surrouding mountains", "cliffs", "northern face",
		   "mountain", "lesser mountain", "jagged cliffs",
		   "black cliffs", "jagged black cliffs"}),
	     "A tall mountain lines the northern side of the valley, while "+
	     "a lesser mountain flanks the valley on the south.\n");

    add_item(({"tall mountain", "north mountain", "northern side",
		 "northern mountain", "southern flank"}),
	     "The mountain to your north towers hundreds of metres above "+
	     "the valley. Its southern flank is steeply inclined and marred "+
	     "by frequent expanses of bare black rock.\n");

    add_item(({"lesser mountain", "south mountain", "southern mountain",
		 "top", "roundish top"}),
	     "South of the valley rises a small mountain, a few hundred "+
	     "metres in height with a roundish top.\n");

      
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_44", "east", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_42", "northwest", 0, 5);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}






