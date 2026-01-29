/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/

#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Ridge on the lower slopes of a mountain.");
    set_em_long("Atop a pine-encrusted ridge on the lower slopes "+
		"of a mountain. The terrain here is rocky, making "+
		"the woods light. The "+
		"ridge ascends the mountain to the east, and "+
		"descends from it to the west.\n");

    add_item(({"mountain", "east mountain", "lesser peak", "peak",
		 "near mountain"}),
	     "The ridge leads upwards on the lower slopes of a "+
	     "small mountain. From what you can see, much of it "+
	     "is composed of towering cliffs. The top of the "+
	     "mountain is gently rounded, however.\n");

    add_item(({"ground", "earth", "down", "soil", "bedrock",
		   "black bedrock"}),
	     "The soil cover here is quite thin in places and quite "+
	     "rocky. Exposed sections of black bedrock are not "+
	     "uncommon.\n");

    add_item(({"vegetation", "trees", "pines", "pine trees", 
		 "jack pines", "conifers"}),
	   "You are within a stand of jack pine. Short conifers "+
	   "of a scraggly appearance, their lock on the ridge "+
	   "is disturbed only by the occasional bush, or competing "+
	   "tree species.\n");

    add_item(({"cliffs", "towering cliffs", "black rock", "rock"}),
	     "You cliffs are composed of a black rock, and might be "+
	     "as tall as several hundred metres. You can make out no "+
	     "details from here.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_27", "west", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_38", "east", 0, 4);  
}

/* Default smells for this room. */

public void
hook_smelled(string arg)
{
    if (!strlen(arg) || parse_command(arg, ({}), "[the] 'pines' / "+
	"'forest' / 'trees' / 'conifers'"))
    {
	write("The distinctive smell of pine needles permeates the air.\n");
	return;
    }   
}







