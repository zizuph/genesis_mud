/* File: /d/Shire/common/trollsh/shaws4.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/


create_shawrom()
{

    set_short("Southeast on a small ridge.");
    set_extraline("You are situated on the southeast edge of one "
	+"of the ridges here in the Trollshaws. This place is "
	+"lightly overgrown with bushes. "
	+"To the southeast, down a small slope, you see the "
	+"Eastroad. Walking west or north will take you to "
	+"another part of this ridge. ");

add_item(({"eastroad","road","Eastroad","slope"}),"Down the slope to the southeast "
          +"you see the Great Eastroad.\n");
    
/*    SOUTHEAST("rivend5a");  For the oppening */
    WEST("shaws1");
    NORTH("shaws5");
   
    
}

