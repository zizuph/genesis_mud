/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{   
    ::create_valley_room();
    set_short("Woodlands. North of Telberin, south of the Blackwall mountains.");
    set_em_long("In a moderatly dense forest, north of Telberin. The woods are "+
		"alive with sound: The ceaseless chirping of a myriad of "+
		"bird species, the pitter-patter of small animals as they "+
		"scamper across the forest floor, the rustling of leaves "+
		"in the wind.\n\n"+
		"Glancing north through a break in the forest canopy, one's "+
		"view is dominated by the oppresive form of the Blackwall "+
		"mountains. The stark blackness of their peaks contrasting "+
		"sharply with the luminescent green of the forest.\n");

    add_item("birds",
	     "Small and large, colorful and plain, quiet and raucous: there "+
	     "seems to be no end to the variety of birds which inhabit these "+
	     "woods.\n");

    add_item(({"animals", "small animals"}),
	     "Squirrels, chipmunks and all manner of small animals seem to "+
	     "inhabit these woods.\n");

    add_item(({"forest", "woods", "woodlands", "trees", "leaves", "bushes",
		   "undergrowth", "oak trees", "oaks", "elms", "elm trees",
		 "stately oak trees", "stately elm trees", "oak and elm trees",
		 "stately oak and elm trees", "canopy"}),
	     "The forest is dominated by stately oak and elm trees, with other "+
	     "species growing wherever they can. Some bushes and undergrowth "+
	     "are in evidence, but the forest is generally easy to traverse.\n");

    add_item(({"mountains", "blackwall", "blackwall mountains", "peaks"}),
	     "The foreboding black peaks of the mountains dominate the terrain "+
	     "to the north and west. Wisps of smoke emanate from the highest, "+
	     "and largest mountain, Mount Black.\n");

    add_item(({"mount black", "volcano"}),
	     "The dominant mountain of the range it is also an active volcano.\n");

    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_2", "northeast", 0, 4);
}

void
init()
{
    if (interactive(this_player()))
    catch(call_other(BLACKWALL_VALLEY1_DIR + "valley1_clone_handler", "??")); 

    ::init();
}







