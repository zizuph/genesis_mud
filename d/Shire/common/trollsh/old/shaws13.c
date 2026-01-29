/* File: /d/Shire/common/trollsh/trollsh13.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/

create_shawrom()
{

    set_short("Deep in the Trollshaws on a ridge");
    set_extraline(
	 "You find yourself on a ridge deep in the Trollshaws. "
	+"This part of the ridge is overrun with thick stocky bushes, "
	+"making movement very difficult. You can't even see the ground. "
	+"To the east and west the ridge continues, while a small path to the "
	+"southwest leads down from the ridge. Another way off this ridge is "
	+"to the south. But then you would walk down into a depression and up "
	+"on the other side. ");
    
add_item(({"depression"}),
		 "The depression bends down between the two ridges. "
		+"It is full of bushes making it imposible to move down "
		+"there, exept for the path going through it.\n");

    add_exit(TROLLSH_DIR + "shaws8", "southwest", 0, 1);
    add_exit(TROLLSH_DIR + "shaws12", "south", 0, 1);
    add_exit(TROLLSH_DIR + "shaws25", "north", 0, 1);
    add_exit(TROLLSH_DIR +  "shaws15", "east", 0, 1);
    add_exit(TROLLSH_DIR +  "shaws9", "west", 0, 1);
}
