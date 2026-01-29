/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

#define VALLEY1_DIR "/d/Emerald/blackwall/valley1/"

inherit VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("By a river, in the shadow of the Blackwall mountains.\n");
    set_em_long("Along the northern bank of a river which flows through "+
		"a moderatly thick forest. The vegetation is particularly "+
                "dense along the banks of the stream.\n");

    add_item(({"forest", "woods", "woodlands", "trees"}),
	     "The forest is relativly thin along the river, with an abundance "+
	     "of bushes growing its banks.\n");

    add_item(({"life", "animals", "animal life", "larger animals", "deer"}),
	     "Smaller forest animals such as birds and squirrels are the most "+
	     "abundant inhabitants of the forest. However, you have caught "+
	     "glimpses of movement which suggest that larger animals also "+
	     "inhabit the forest, perhaps deer.\n");

    add_item("river",
	     "A small river, about 30 feet across. The river flows from the "+
	     "mountains in the east, into the vast expanse of forest to the "+
	     "west.\n");
    
    add_item(({"mountains", "peaks", "southerly peaks", "Blackwall Mountains",
		 "Blackwall mountains"}),
	     " The mountain on the northern side of the valley is the higher "+
	     "of the two, its sharp black peak reaching nearly to the clouds. The "+
	     "mountain on the southern side isn't nearly as high, and has a more "+
	     "rounded top. Higher mountains still lie to the north.\n");

    add_exit(VALLEY1_DIR + "valley1_6", "east", 0, 3);
    add_exit(VALLEY1_DIR + "valley1_4", "west", 0, 3);
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




